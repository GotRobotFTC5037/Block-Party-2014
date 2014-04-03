/**
*
*  @file abs_end_ramp.h
*
*  @brief stop point function to end on either ramp
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_END_RAMP_H
#define ABS_END_RAMP_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_dlog.h"
#include "abs_get_angle_sensor_val.h"
#include "abs_control_light_sensor.h"
#include "abs_mission_to_turn_amount.h"
#include "abs_lift_block_lifter.h"

void abs_end_ramp(int delay, int lift_speed)
{
	abs_dlog(__FILE__,"Function Enter", "delay", delay);

	if(g_end_point != 2 && g_end_point !=3)
	{
		abs_dlog(__FILE__,"Function called for incorrect ramp");
		return;
	}

	if(g_start_point == 1 || g_start_point == 2) g_to_turn_dist = g_dist_backwards;
	wait1Msec(delay);
	servo[abdd] = g_abdd_down;

	if(g_mission_number==0&&(g_start_point==1||g_start_point==2))
	{
		if(g_start_point==1)
		{
			if(g_end_point == 2) {g_to_turn_dist = 190;}
			else if(g_end_point == 3) {g_to_turn_dist = 6;}
		}
		else
		{
			if(g_end_point == 2) {g_to_turn_dist = 3;}
			else if(g_end_point == 3) {g_to_turn_dist = 196;}
		}
	}

	if(g_end_point == 2)
	{
		abs_dlog(__FILE__ ,"drive to ramp 1");
		if(g_mission_number==0&&g_start_point==2) abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
		else abs_drive(FORWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
	}
	else
	{
		abs_dlog(__FILE__ ,"drive to ramp 2");
		if(g_mission_number==0&&g_start_point==1) abs_drive(FORWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
		else abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
	}

	if(abs_get_angle_sensor_val(RELATIVE_BPU) < 5 && g_mission_number !=0)
	{
		abs_dlog(__FILE__,"dist fail","rel BPU", abs_get_angle_sensor_val(RELATIVE_BPU));
		motor[left_motor] = 0;
		motor[right_motor] = 0;
		PlayTone(300,200);
		return;
	}

	wait1Msec(200);
#if EOPD_ACTIVE == 0
	abs_control_light_sensor(ACTIVE);
#endif
	servo[optical_servo] = OPTICAL_SERVO_DOWN;

	if(g_good_gyro && g_em_first_turn_type == CONSTANT_TURN)
	{
		abs_dlog(__FILE__ ,"first turn: good gyro");
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, abs_mission_to_turn_amount(g_start_point, g_end_point, true/*g_good_gyro*/), 40);//was 60
	}
	else
	{
		abs_dlog(__FILE__ ,"first turn: bad gyro");
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, abs_mission_to_turn_amount(g_start_point, g_end_point, false/*g_good_gyro*/), 40);//was 60
	}

	wait1Msec(g_input_array[CORNOR_DELAY]*DELAY_MULTIPLICATION_FACTOR);
	wait1Msec(200);
	abs_drive(FORWARD, E_OPTICAL, 105, 30, true, GYRO);
	if(abs_get_angle_sensor_val(RELATIVE_BPU) < 80)
	{
		if(g_mission_number!=0)abs_drive(FORWARD, E_ANGLE, 102 - abs_get_angle_sensor_val(RELATIVE_BPU), 30, true, GYRO);
		else abs_drive(FORWARD, E_ANGLE, 105 - abs_get_angle_sensor_val(RELATIVE_BPU), 30, true, GYRO);
	}
	if(g_auto_sub_selection_ramp_side == SUB_SELECTION_RAMP_OPP_SIDE)
	{
		servo[optical_servo] = OPTICAL_SERVO_DOWN;
		abs_drive(FORWARD, E_ANGLE, DRIVE_DIST_TO_OPP_RAMP_SIDE - abs_get_angle_sensor_val(RELATIVE_BPU), 30, false, GYRO);
		abs_drive(FORWARD, E_OPTICAL, 24, 30, true, GYRO);
	}

	abs_control_light_sensor(INACTIVE);
	wait1Msec(500);
	StartTask(abs_lift_block_lifter);

	if(g_good_gyro && g_em_first_turn_type == CONSTANT_TURN)
	{
		if(g_end_point == 2)
		{
			abs_dlog(__FILE__ ,"second turn: good gyro");
			if(g_auto_sub_selection_ramp_side == SUB_SELECTION_RAMP_ALLY_SIDE) abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 183, 40);//was 60
			else	abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 187, 40);//was 60
		}
		else
		{
			abs_dlog(__FILE__ ,"second turn: bad gyro");
			if(g_auto_sub_selection_ramp_side == SUB_SELECTION_RAMP_ALLY_SIDE) abs_turn(CLOCKWISE, POINT, TURN_TO, 357, 40);//was 50
			else abs_turn(CLOCKWISE, POINT, TURN_TO, 355, 40);//was 50
		}
	}
	else
	{
		if(g_end_point == 2)
		{
			if(g_auto_sub_selection_ramp_side == SUB_SELECTION_RAMP_ALLY_SIDE) abs_turn(COUNTERCLOCKWISE, POINT, TURN, 87, 60);
			else abs_turn(COUNTERCLOCKWISE, POINT, TURN, 85, 60);
		}
		else
		{
			if(g_auto_sub_selection_ramp_side == SUB_SELECTION_RAMP_ALLY_SIDE) abs_turn(CLOCKWISE, POINT, TURN, 85, 50);
			else abs_turn(CLOCKWISE, POINT, TURN, 87, 50);
		}
	}
	/** before entering the ramp, pause for the requested time */
	wait1Msec(g_input_array[RAMP_DELAY] * DELAY_MULTIPLICATION_FACTOR);

	if(g_auto_selection_ramp_continue_options == SUB_SELECTION_RAMP_STOP) abs_drive(FORWARD, E_ANGLE, 80, 50, true, GYRO);
	else abs_drive(FORWARD, E_ANGLE, 130, 50, true, GYRO);

	//if the lift task is still running at this point then stop it
	StopTask(abs_lift_block_lifter);
}

#endif /* !ABS_S1_END_RAMP_H */
