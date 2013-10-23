/**
*
*  @file abs_point_turn_to.h
*
*  @brief The hedder file that alows you to do a point turn
*
*  @param degree Tells the robot how much to turn
*
*  @param dir Tells the robot what way to turn
*
*  @param speed Tells the robot how fast to turn
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SWING_TURN_TO_H
#define ABS_SWING_TURN_TO_H

#include "xzander/hitechnic-gyro.h"
#include "abs_move_utils.h"
#include "abs_gyro_read.h"
#include "abs_get_mem.h"
#include "abs_report_error.h"
/** macros */


//=======================================
// point turn
//=======================================
void abs_turn(e_direction dir, e_turn_method turn_method, int degree, int speed)
{
	int i = 0;
	//float rotSpeed = 0;
	//float heading = 0;
	turn_context* tcontext = 	(turn_context*)abs_get_mem(sizeof(turn_context));

	if(tcontext == NULL)
	{
		abs_report_error(NULL_POINTER);
	}
	tcontext->time = 0;
	tcontext->heading = 0;
	if(turn_method == SWING)
	{
		if(dir == COUNTERCLOCKWISE)
		{
			motor[right_motor] = speed;
			motor[left_motor] = 0;
		}
		else
		{
			motor[right_motor] = 0;
			motor[left_motor] = speed;
		}
	}
	else if(turn_method == POINT)
	{
		if(dir == COUNTERCLOCKWISE)
		{
			motor[right_motor] = speed;
			motor[left_motor] = -speed;
		}
		else
		{
			motor[right_motor] = -speed;
			motor[left_motor] = speed;
		}
	}
	//gyro pre turn start
	while(i < 5)
	{
		if (abs(tcontext->heading) > degree) i++;
		nxtDisplayCenteredBigTextLine(1, "%d", degree);
		abs_gyro_read(HTGYRO,tcontext); //gyro read

		//heading += rotSpeed * 0.02;

		//nxtDisplayCenteredBigTextLine(1, "%2.0f", tcontext->heading);
		//nxtDisplayCenteredBigTextLine(3, "%d", degree);
		//nxtDisplayCenteredBigTextLine(5, "%d", SensorValue(HTGYRO));
	}
	motor[right_motor] = 0;
	motor[left_motor] = 0;
}

//#define product(X, Y) ((X) * (Y))
//#define sum(X, Y) ((X) + (Y))
//#define min(X, Y) ((X) < (Y) ? (X) : (Y))
//#define max(X, Y) ((X) > (Y) ? (X) : (Y))

#endif /* !ABS_SWING_TURN_TO_H */
