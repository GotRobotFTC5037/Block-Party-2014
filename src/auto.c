#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     GYRO_MUX,       sensorI2CCustom)
#pragma config(Sensor, S3,     SENSOR_MUX,     sensorI2CCustom)
#pragma config(Sensor, S4,     angle_sensor,   sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     block_lift_motor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     sky_hook,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     jolly_roger,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     right_motor,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     left_motor,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    grabber_right,        tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabber_left,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    roger_slide,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    light_sensor,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    abdd,                 tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
*
*  @file auto.c
*
*  @brief The automatic program for the robot.
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

/*Includes*/

//-----------------------
// sensor/mux/joystick includes
//-----------------------

#include "joystickdriver.c"
#include "lib/xander/hitechnic-sensormux.h"
#include "lib/xander/hitechnic-irseeker-v2.h"
#include "lib/xander/hitechnic-gyro.h"
#include "lib/xander/hitechnic-angle.h"
#include "lib/xander/hitechnic-accelerometer.h"

//-----------------------
// custom functions includes
//-----------------------

#include "lib/global_varaibles.h"
#include "lib/abs_selection_program.h"
#include "lib/abs_screen.h"
#include "lib/abs_gyro_cal.h"
#include "lib/math_utils.h"
#include "lib/abs_sensors.h"
#include "abs_move_utils.h"
#include "lib/abs_turn.h"
#include "abs_gyro_drive.h"
#include "lib/abs_drive.h"
#include "lib/abs_initialize.h"
#include "lib/abs_motor.h"

//========================================
// Main program
//========================================

task main()
{
	initialize();
	switch(start_point)
	{
	case 1:
		switch(mission_number)
		{
		case 0:
			abs_turn(CLOCKWISE, POINT, TURN, 180, 60);
			wait10Msec(300);
			abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
			wait10Msec(300);
			abs_turn(CLOCKWISE, POINT, TURN, 45, 60);
			wait10Msec(300);
			abs_turn(COUNTERCLOCKWISE, POINT, TURN, 0, 60);
			break;

		case 1:
			abs_drive(FORWARD, E_IR_DETECT, 0, 40, true);
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/15, 50, true);
			wait1Msec(500);
			servo[abdd] = ABDD_UP;
			wait1Msec(2000);
			servo[abdd] = ABDD_DOWN;
			wait1Msec(2000);
			break;

		case 2:
			to_turn_dist= crate4_to_turn_dist;
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/150, 50, true);
			servo[abdd] = ABDD_UP;
			wait1Msec(2000);
			servo[abdd] = ABDD_DOWN;
			break;

		case 3:
			to_turn_dist= crate3_to_turn_dist;
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/125, 50, true);
			servo[abdd] = ABDD_UP;
			wait1Msec(2000);
			servo[abdd] = ABDD_DOWN;
			wait1Msec(2000);

			break;

		case 4:
			to_turn_dist= crate2_to_turn_dist;
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/75, 50, true);
			servo[abdd] = ABDD_UP;
			wait1Msec(2000);
			servo[abdd] = ABDD_DOWN;
			wait1Msec(2000);

			break;

		case 5:
			to_turn_dist= crate1_to_turn_dist;
			abs_drive(FORWARD, E_ANGLE, /*distance in cm*/50, 50, true);
			servo[abdd] = ABDD_UP;
			wait1Msec(2000);
			servo[abdd] = ABDD_DOWN;
			wait1Msec(2000);

			break;

		case 140:
			int dist = 30;
			bool done = false;
			while(done == false)
			{
				int ac_start_time = nPgmTime;
				int i = 0;
				while((accelermoeter_sensor < dist+5) && (accelermoeter_sensor > dist-5) && ((ac_start_time - nPgmTime)<500))
				{
					i++;
					PlayTone(20,20);
					wait1Msec(1);
				}
				if(i > 490) done = true;
				PlayTone(20,20);
			}
			break;
		}
		break;
	}
	switch(end_point)
	{
	case 1:
		motor[right_motor] = 0;
		motor[left_motor] = 0;
		motor[sky_hook] = 0;
		motor[block_lift_motor] = 0;
		break;
	case 2:
		wait1Msec(2000);
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/to_turn_dist, 50, true);
		wait1Msec(1000);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		break;
	}
}
