/**
*
*  @file abs_joystick_drive.h
*
*  @brief The header file that handles the joystick motor control
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_JOYSTICK_DRIVE_H
#define ABS_JOYSTICK_DRIVE_H

#include "abs_teleop_utils.h"
/** macros */
//=======================================
// joystick drive
//=======================================
void abs_joystick_drive(e_joystick_method joy_method)//int joy1,int joy2)
{
	e_joystick_method method = joy_method;

		int joy1 = joystick.joy1_y1;
		int joy2 = joystick.joy1_y2;

		int speed1;
		int speed2;

		int j1 = abs(joy1);
		int j2 = abs(joy2);

		if(method == LINEAR)
		{

			speed1 = j1*100/127;
			speed2 = j2*100/127;

			if(speed1<10) speed1 = 0;
			if(speed2<10) speed2 = 0;

			nxtDisplayBigTextLine(0,"%d",speed1);

			if(joy1<0) speed1 = -speed1;
			if(joy2<0) speed2 = -speed2;
		}
		else
		{
			speed1 = ((j1*j1) * 100/(128*128));
			speed2 = ((j2*j2) * 100/(128*128));
		}

		if(speed1<10) speed1 = 0;
		if(speed2<10) speed2 = 0;

		nxtDisplayBigTextLine(0,"%d",speed1);

		if(joy1<0) speed1 = -speed1;
		if(joy2<0) speed2 = -speed2;

		motor[right_motor] = speed1;
		motor[left_motor] = speed2;

}

#endif /* !ABS_JOYSTICK_DRIVE_H */
