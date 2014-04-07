/**
 *
 *  @file abs_gyro_drive.h
 *
 *  @brief handles the speed control for the motors based on the gyro
 *
 *  @param speed tells the robot how fast to go
 *
 *  @param dir Tells the robot what direction to go
 *
 *  @return Returns nothing
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */
#ifndef ABS_GYRO_DRIVE_H
#define ABS_GYRO_DRIVE_H

#include "abs_move_utils.h"

void abs_gyro_drive(int speed,e_drive_direction dir)
{
	int error = 0 - g_rel_heading;

	if(dir == FORWARD)
	{
		motor[left_motor] = speed + (error*g_gyro_adjust);
		motor[right_motor] = speed - (error*g_gyro_adjust);
	}
	else
	{
		motor[left_motor] = -(abs(speed) - (error*g_gyro_adjust));
		motor[right_motor] = -(abs(speed) + (error*g_gyro_adjust));
	}
}
#endif /* !ABS_GYRO_DRIVE_H */
