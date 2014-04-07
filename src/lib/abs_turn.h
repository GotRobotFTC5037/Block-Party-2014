/**
*
*  @file abs_turn.h
*
*  @brief The header file that alows you to do a point turn
*
*  @param degree Tells the robot how much to turn
*
*  @param dir Tells the robot what way to turn
*
*  @param speed Tells the robot how fast to turn
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_TURN_H
#define ABS_TURN_H

#include "abs_dlog.h"
#include "abs_turn_speed_ctrl.h"

/** macros */

//=======================================
// point turn
//=======================================
void abs_turn(e_direction dir, e_turn_method turn_method, e_turn_stopping_method e_stop, int degree, int speed)
{
        if(dir == COUNTERCLOCKWISE)
                abs_dlog(__FILE__ ,"enter CC","speed", speed, "degree", degree, "g_rel_heading", g_rel_heading, "g_const_heading", g_const_heading);
        else
                abs_dlog(__FILE__ ,"enter C", "speed", speed, "degree", degree, "g_rel_heading", g_rel_heading, "g_const_heading", g_const_heading);

	int i = 0;
	g_rel_heading = 0;
	int target = 0;

	if(e_stop == TURN_TO)
	{
		if(dir == COUNTERCLOCKWISE)
		{
			if(degree<g_recont_heading) target = -(g_recont_heading-degree);
			else target = -(360-(degree-g_recont_heading));
		}
		else
		{
			if(degree<g_recont_heading) target = 360-(g_recont_heading-degree);
			else target = degree-g_recont_heading;
		}
		abs_turn(dir, turn_method, TURN, target, speed);
		PlaySoundFile("! Click.rso");
	}
	else
	{
		//-------------------------
		// swing turn
		//-------------------------
		while(abs(g_rel_heading) < abs(degree))
		{
			int turn_speed = adjusted_turn_speed(speed, abs(degree), abs(g_rel_heading));

			if(turn_method == SWING)
			{
				if(dir == COUNTERCLOCKWISE)
				{
					motor[right_motor] = turn_speed;
					motor[left_motor] = 0;
				}
				else
				{
					motor[right_motor] = 0;
					motor[left_motor] = turn_speed;
				}
			}

			//-------------------------
			// point turn
			//-------------------------
			else
			{
				if(dir == COUNTERCLOCKWISE)
				{
					motor[right_motor] = turn_speed;
					motor[left_motor] = -turn_speed;
				}
				else
				{
					motor[right_motor] = -turn_speed;
					motor[left_motor] = turn_speed;
				}
			}
		}
	}
	//-------------------------
	// turn condition
	//-------------------------

	if(e_stop == TURN)
	{
		while(abs(g_rel_heading) < abs(degree)){}
		motor[right_motor] = 0;
		motor[left_motor] = 0;
	}

	abs_dlog(__FILE__ ,"exit", "speed", speed, "degree", degree, "g_rel_heading", g_rel_heading, "g_const_heading", g_const_heading);
}

#endif /* !ABS_TURN_H */
