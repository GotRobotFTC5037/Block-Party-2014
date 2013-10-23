/**
*
*  @file template.h (this should be the name of the function)
*
*  @brief  Enter a description of what this function does
*
*  @param
*
*  @return
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_DRIVE_H
#define ABS_DRIVE_H

#include "xzander/hitechnic-angle.h"
#include "abs_gyro_drive.h"


/** macros */
//=========================
//Drive
//=========================
void abs_drive(e_drive_direction dir, e_stopping_method dist_method, int dist, int speed)
{
	HTANGresetAccumulatedAngle(ANGLE_SENSOR);
	int i = 0;
	nMotorEncoder(right_motor)= 0;
	turn_context* tcontext = 	(turn_context*)abs_get_mem(sizeof(turn_context));
	tcontext->time = 0;
	tcontext->heading = 0;
	abs_gyro_read(HTGYRO,tcontext);

	if(dir == FORWARD)  //Decides if you are driveing forwards or backwards
	{
		motor(right_motor)=speed;
		motor(left_motor)=speed;
	}
	else
	{
		motor(right_motor)=-speed;
		motor(left_motor)=-speed;
	}

	if(dist_method == E_TIME)   //time stopping method
	{
		ClearTimer(T1);
		while(time1[T1] < dist)
		{
			abs_gyro_drive(tcontext,speed);
		}
		//wait1Msec(dist);
	}
	else if(dist_method == E_ROTATIONS)  //encoder stopping method
	{
		while(i<5)
		{
			if(abs(nMotorEncoder(right_motor)) > dist*360)
				i++;
			abs_gyro_drive(tcontext,speed);
		}
	}
	else
	{
		if(dir == FORWARD)
		{
			while(HTANGreadAccumulatedAngle(ANGLE_SENSOR) < distance_to_angle_derees(dist))
			{
				abs_gyro_drive(tcontext,speed);
			}

		}
		else
		{
			while(HTANGreadAccumulatedAngle(ANGLE_SENSOR) < distance_to_angle_derees(-dist))
			{
				abs_gyro_drive(tcontext,speed);
			}

		}
		motor(left_motor)=0;
		motor(right_motor)=0;
	}
}


/** enumerations */

/** structures */

/** function prototypes */

/** global constant variables */

#endif /* !ABS_DRIVE_H */
