/**
*
*  @file abs_gyro_drive_to.h
*
*  @brief handles the speed control for the motors based on the gyro
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_GYRO_DRIVE_H
#define ABS_GYRO_DRIVE_H

/** macros */


//=======================================
// gyro drive
//=======================================
void abs_gyro_drive(move_context* tcontext,int speed)
{
	int error = 0 - tcontext->heading;
	//tcontext->heading) > degree

	motor[left_motor] = speed + error;
	motor[right_motor] = speed - error;
}
#endif /* !ABS_GYRO_DRIVE_H */
