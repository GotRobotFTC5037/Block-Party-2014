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
#include "abs_log.h"
#include "abs_get_angle_sensor_val.h"
#include "abs_control_light_sensor.h"
#include "abs_mission_to_turn_amount.h"
#include "abs_lift_block_lifter.h"
#include "global_variables.h"

void abs_end_ramp(int delay)
{
	abs_log(__FILE__,"Function Enter",delay,0,0,0);		//enter and log the begining of the end mission

	if(g_end_point != 2 && g_end_point !=3)						//2 & 3 are the only valid ramp options, if any other option is
	{																									//selected send an error and exit the program
		abs_log(__FILE__,"Function called for incorrect ramp",0,0,0,0);
		return;
	}

	if(g_start_point == 1 || g_start_point == 2) g_to_turn_dist = g_dist_backwards;//set the drive distance to recorded
	wait1Msec(delay);						//wait the amount selected in auto.c							 //delivery distance if started at 1 or 2
	servo[abdd] = g_abdd_down;	//comfirm the abdd is down to avoid driving it into field objects

	if(g_end_point == 2)				//if the end ramp goal is point 1 (input of 2) drive forwards to wall
	{
		abs_dlog(__FILE__ ,"drive to ramp 1");	//log ramp decision
		abs_drive(FORWARD, E_ANGLE, g_to_turn_dist, end_program_drive_speed, true, g_drive_type);
	}
	else												//if the end ramp goal is point 2 (input of 3) drive backwards to wall
	{
		abs_dlog(__FILE__ ,"drive to ramp 2");	//log ramp decision
		abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, end_program_drive_speed, true, g_drive_type);
	}

	if(abs_get_angle_sensor_val(RELATIVE_BPU) < 5)//15)	//robot movement error detection, if robot has not moved min distance
	{																										//to reach wall from crate assume the robot has failed and stop moving
		abs_log(__FILE__,"dist fail",abs_get_angle_sensor_val(RELATIVE_BPU),0,0,0);	//log error and end program
		motor[left_motor] = 0;
		motor[right_motor] = 0;
		PlayTone(300,200);
		return;
	}
	wait1Msec(200);
	abs_control_light_sensor(ACTIVE);				//turn on light sensor for line detection
	servo[light_sensor] = LIGHT_SERVO_DOWN;	//and lower the light sensor into position

	if(g_good_gyro && g_em_first_turn_type == END_MISSION_FIRST_TURN_CONST)	//if the gyro is detected as good and 1st turn sub
	{																																				//menu option is selected as true use const turn
		abs_dlog(__FILE__ ,"first turn: good gyro");	//log turn type conclusion as const
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, abs_mission_to_turn_amount(g_start_point, g_end_point, g_good_gyro), 40);//was 60
	}
	else
	{
		abs_dlog(__FILE__ ,"first turn: gyro gyro");	//log turn type conclusion as rel
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, abs_mission_to_turn_amount(g_start_point, g_end_point, false), 40);//was 60
	}

	wait1Msec(g_input_array[CORNOR_DELAY]*DELAY_MULTIPLICATION_FACTOR);	//wait for corner delay amount, this is only an option
	wait1Msec(200);																											//in the advanced selection
	abs_drive(FORWARD, E_LIGHT, MAX_DRIVE_DIST_TO_FIRST_RAMP_LINE, 30, true, g_drive_type);	//drive looking for the line
	if(abs_get_angle_sensor_val(RELATIVE_BPU) < MIN_DRIVE_DIST_TO_FIRST_RAMP_LINE)	//check for dist travel is less then min
	{																																								//dist, if so make up needed dist
		abs_dlog(__FILE__ ,"backup, min dist fail", "Cur dist: %d", abs_get_angle_sensor_val(RELATIVE_BPU), "Min dist: %d", MAX_DRIVE_DIST_TO_FIRST_RAMP_LINE - abs_get_angle_sensor_val(RELATIVE_BPU));
		abs_drive(FORWARD, E_ANGLE, MAX_DRIVE_DIST_TO_FIRST_RAMP_LINE - abs_get_angle_sensor_val(RELATIVE_BPU), 30, true, g_drive_type);
	}
	abs_control_light_sensor(INACTIVE);	//turn off the light sensor
	wait1Msec(500);
	StartTask(abs_lift_block_lifter);	//raise the block lift to drive onto ramp safely

	if(g_good_gyro && g_em_first_turn_type == END_MISSION_SECOND_TURN_CONST)//if the gyro is detected as good and 1st turn sub
	{																																				//menu option is selected as true use const turn
		if(g_end_point == 2)	//if end point is ramp 1 turn to the left so grabbers drive first
		{
			abs_dlog(__FILE__ ,"second turn: good gyro");	//log turn type conclusion as const
			abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 180, end_program_drive_speed);//was 60
		}
		else	//else: if end point is ramp 2 turn to the left so grabbers drive first
		{
			abs_dlog(__FILE__ ,"second turn: good gyro");	//log turn type conclusion as rel
			abs_turn(CLOCKWISE, POINT, TURN_TO, 0, end_program_drive_speed);//was 50
		}
	}
	else
	{
		if(g_end_point == 2)	//if end point is ramp 1 turn to the left so grabbers drive first
		{
			abs_dlog(__FILE__ ,"second turn: bad gyro");
			abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, end_program_drive_speed);
		}
		else	//else: if end point is ramp 2 turn to the left so grabbers drive first
		{
			abs_dlog(__FILE__ ,"second turn: bad gyro");
			abs_turn(CLOCKWISE, POINT, TURN, 90, end_program_drive_speed);
		}
	}
	/** before entering the ramp, pause for the requested time */
	wait1Msec(g_input_array[RAMP_DELAY] * DELAY_MULTIPLICATION_FACTOR);

	//drive to closest for farthest ramp spot based on auto selection input
	if(g_auto_grabber_selection_ramp_options == SUB_SELECTION_RAMP_STOP) abs_drive(FORWARD, E_ANGLE, 80, end_program_drive_speed, true, g_drive_type);
	else abs_drive(FORWARD, E_ANGLE, 130, end_program_drive_speed, true, g_drive_type);

	//if the lift task is still running at this point then stop it
	StopTask(abs_lift_block_lifter);
}

#endif /* !ABS_S1_END_RAMP_H */
