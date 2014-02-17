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

void abs_end_ramp(int delay, int lift_speed)
{
	abs_log(__FILE__,"Function Enter",delay,lift_speed,0,0);

        if(g_end_point != 2 && g_end_point !=3)
        {
	  abs_log(__FILE__,"Function called for incorrect ramp",0,0,0,0);
          return;
        }

	if(g_mission_number == 1)g_to_turn_dist = g_dist_backwards;
	dl_step = dl_step+1;
	dl_robot_action_state = dl_wait;
	dl_speed = delay;
	wait1Msec(delay);
	servo[abdd] = g_abdd_down;

        if(g_end_point == 2)
        {
	  abs_drive(FORWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
        }
        else
        {
	  abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
        }

	if(abs_get_angle_sensor_val(RELATIVE_BPU) < 5)//15)
	{
		abs_log(__FILE__,"dist fail",abs_get_angle_sensor_val(RELATIVE_BPU),0,0,0);
		motor[left_motor] = 0;
		motor[right_motor] = 0;
		PlayTone(300,200);
		return;
	}

	dl_step = dl_step+1;
	dl_robot_action_state = dl_wait;
	dl_speed = 200;
	wait1Msec(200);
	abs_control_light_sensor(ACTIVE);
	servo[light_sensor] = LIGHT_SERVO_DOWN;
	abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, abs_mission_to_turn_amount(g_start_point, g_end_point), 60);

	dl_step = dl_step+1;
	dl_robot_action_state = dl_wait;
	dl_speed = 200;
	wait1Msec(200);
	abs_drive(FORWARD, E_LIGHT, 110, 30, true, GYRO);
	dl_step = dl_step+1;
	dl_robot_action_state = dl_wait;
	dl_speed = 500;
	wait1Msec(500); //***
	motor[block_lift_motor] = lift_speed;
	motor[block_lift_motor2] = lift_speed;

        if(g_end_point == 2)
        {
	  abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 180, 60);
        }
        else
        {
	  abs_turn(CLOCKWISE, POINT, TURN_TO, 0, 50);
        }
	motor[block_lift_motor] = 0;
	motor[block_lift_motor2] = 0;

        /** before entering the ramp, pause for the requested time */
	wait1Msec(g_ramp_delay * DELAY_MULTIPLICATION_FACTOR);

	if(g_auto_grabber_selection_ramp_options == SUB_SELECTION_RAMP_STOP) abs_drive(FORWARD, E_ANGLE, 80, 50, true, GYRO);
	else abs_drive(FORWARD, E_ANGLE, 130, 50, true, GYRO);
}

#endif /* !ABS_S1_END_RAMP_H */