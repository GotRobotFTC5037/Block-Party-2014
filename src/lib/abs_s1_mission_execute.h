/**
*
*  @file abs_s1_mission_execute.h
*
*  @brief runs the missions from the starting point S1
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_S1_MISSION_EXECUTE_H
#define ABS_S1_MISSION_EXECUTE_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_stop_robot.h"
#include "abs_end_ramp.h"
#include "abs_dlog.h"
#include "abs_get_angle_sensor_val.h"
#include "lib/abs_cscreen.h"
#include "lib/abs_calibrate_optical.h"

void abs_s1_mission_execute()
{
	switch(g_mission_number)
	{
	case 0:
		break;

	case 1:
		dist_record=true;
		abs_drive(FORWARD, E_IR_DETECT, 7, 40, true, GYRO);
		if(abs_get_angle_sensor_val(RELATIVE_BPU) < 38)
		{
			dist_record = true;
			abs_drive(FORWARD, E_ANGLE, 40 - abs_get_angle_sensor_val(RELATIVE_BPU), 40, true, GYRO);
		}
		PlayTone(200,20);
		wait1Msec(1000);
		wait1Msec(500);
		break;

	case 2:
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/150, 50, true, GYRO);

		wait1Msec(2000);
		break;

	case 3:
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/125, 50, true, GYRO);
		break;

	case 4:
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/75, 50, true, GYRO);
		break;

	case 5:
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/50, 50, true, GYRO);
		break;

	case 6:
		motor[right_motor] = 0;
		motor[left_motor] = 0;
		servo[optical_servo] = OPTICAL_SERVO_DOWN;
		while(true){abs_cscreen("Optical ","Sensor","%1d ",g_optical_sensor);}
		break;

	case 7:
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 98, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 87, 50, true, GYRO);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		abs_turn(CLOCKWISE, POINT, TURN, 103, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		abs_drive(FORWARD, E_ANGLE, 80, 50, true, GYRO);
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

	abs_dlog(__FILE__,"start of end", "g_end_point", g_end_point);
}

#endif /* !ABS_S1_MISSION_EXICUTE_H */
