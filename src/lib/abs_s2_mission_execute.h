/**
*
*  @file abs_s2_mission_execute.h
*
*  @brief runs the missions from the starting point S2
*
*  @param None n/a
*
*  @return returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_S2_MISSION_EXECUTE_H
#define ABS_S2_MISSION_EXECUTE_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_stop_robot.h"
#include "abs_end_ramp.h"
#include "abs_dlog.h"
#include "abs_get_angle_sensor_val.h"

void abs_s2_mission_execute()
{
	switch(g_mission_number)
	{
	case 0:
		break;

	case 1:
		dist_record=true;
		abs_drive(BACKWARD, E_IR_DETECT, 3, IR_DRIVE_SPEED, true, GYRO);
		g_shift_due_to_ir = true;
		if(abs_get_angle_sensor_val(RELATIVE_BPU) < 38)
		{
			dist_record = true;
			//g_shift_due_to_ir = false;
			abs_drive(BACKWARD, E_ANGLE, 40 - abs_get_angle_sensor_val(RELATIVE_BPU), IR_DRIVE_SPEED, true, GYRO);
		}
		//Only use g_shift_due_to_ir when shifted due the the ir detecting
		PlayTone(200,20);
		if(g_shift_due_to_ir)
		{
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/6, NON_IR_DRIVE_SPEED, true, GYRO);
		}
		wait1Msec(500);
		break;

	case 2:
		dist_record=true;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/40, NON_IR_DRIVE_SPEED, true, GYRO);
		break;

	case 3:
		dist_record=true;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/65, NON_IR_DRIVE_SPEED, true, GYRO);
		break;

	case 4:
		dist_record=true;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/115, NON_IR_DRIVE_SPEED, true, GYRO);
		break;

	case 5:
		dist_record=true;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/140, NON_IR_DRIVE_SPEED, true, GYRO);
		wait1Msec(2000);
		break;

	case 6:
		abs_turn(CLOCKWISE, POINT, TURN, 75, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 190, NON_IR_DRIVE_SPEED, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 75, 60);
		abs_drive(FORWARD, E_ANGLE, 80, NON_IR_DRIVE_SPEED, true, GYRO);
		break;

	case 7:
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 98, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 87, NON_IR_DRIVE_SPEED, true, GYRO);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		abs_turn(CLOCKWISE, POINT, TURN, 103, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		abs_drive(FORWARD, E_ANGLE, 80, NON_IR_DRIVE_SPEED, true, GYRO);
		break;
	}
	if(g_mission_number != 0)
	{
		abs_dlog(__FILE__,"abdd up");
		servo[abdd] = g_abdd_up;
		StartTask (abs_calibrate_optical);
		wait1Msec(2000);
		servoChangeRate[abdd] = 10;
		servo[abdd] = g_abdd_down;
		abs_dlog(__FILE__,"abdd down");
	}

	wait1Msec(g_end_delay * DELAY_MULTIPLICATION_FACTOR);
	wait1Msec(100);
}

#endif /* !ABS_S2_MISSION_EXECUTE_H */
