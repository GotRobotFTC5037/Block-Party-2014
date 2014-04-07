/**
 *
 *  @file abs_s3_mission_execute.h
 *
 *  @brief runs the missions from the starting point S3
 *
 *  @param None n/a
 *
 *  @return returns nothing
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */

#ifndef ABS_S3_MISSION_EXECUTE_H
#define ABS_S3_MISSION_EXECUTE_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_stop_robot.h"
#include "abs_end_ramp.h"
#include "abs_dlog.h"

void abs_s3_mission_execute()
{
	switch(g_mission_number)
	{
	case 1:
		abs_drive(FORWARD, E_ANGLE, 5, 30, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 320/*was 315*/, 40);
		abs_drive(FORWARD, E_ANGLE, 40, 60, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 40, 30);
		abs_drive(FORWARD, E_IR_DETECT, 7, 40, true, GYRO);
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/3, 50, true, GYRO);
		break;

	case 2:
		abs_drive(FORWARD, E_ANGLE, 5, 30, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 320/*was 315*/, 40);
		abs_drive(FORWARD, E_ANGLE, 40, 60, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 40, 30);
		abs_drive(FORWARD, E_ANGLE, 90, 50, true, GYRO);
		if(g_end_point == 3)g_to_turn_dist = 145;
		else g_to_turn_dist = g_forward_crate4_to_turn_dist;
		break;

	case 3:
		abs_drive(FORWARD, E_ANGLE, 5, 30, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 320/*was 315*/, 40);
		abs_drive(FORWARD, E_ANGLE, 40, 60, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 40, 30);
		abs_drive(FORWARD, E_ANGLE, 60, 35, true, GYRO);
		if(g_end_point == 3)g_to_turn_dist = 120;
		else g_to_turn_dist = g_forward_crate3_to_turn_dist;
		break;

	case 4:
		abs_drive(FORWARD, E_ANGLE, 5, 30, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 320/*was 315*/, 40);
		abs_drive(FORWARD, E_ANGLE, 40, 60, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 40, 25);
		abs_drive(FORWARD, E_ANGLE, 10, 50, true, GYRO);
		if(g_end_point == 3)g_to_turn_dist = 70;
		else g_to_turn_dist = g_forward_crate2_to_turn_dist;
		break;

	case 5:
		abs_drive(FORWARD, E_ANGLE, 5, 30, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN_TO, 320/*was 315*/, 40);
		abs_drive(FORWARD, E_ANGLE, 40, 60, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 40, 30);
		if(g_end_point == 3) g_to_turn_dist = 45;
		else if(g_end_point == 2) g_to_turn_dist = g_forward_crate1_to_turn_dist+5;
		break;

	case 6:
		abs_turn(COUNTERCLOCKWISE, SWING, TURN_TO, 315, 60);
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/30, 50, true, GYRO);
		abs_turn(CLOCKWISE, POINT, TURN_TO, 35, 60);
		abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, 50, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		abs_drive(FORWARD, E_ANGLE, 180, 50, true, GYRO);
		break;

	case 7:
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

#endif /* !ABS_S3_MISSION_EXECUTE_H */
