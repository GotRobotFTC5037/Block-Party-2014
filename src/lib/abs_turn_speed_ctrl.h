/**
*
*  @file abs_turn_speed_ctrl.h
*
*  @brief  ctrls the speed in turning to help make a better turn
*
*  @param speed
*
*  @param turn type
*
*  @param direction
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/

#ifndef ABS_TURN_SPEED_CTRL_H
#define ABS_TURN_SPEED_CTRL_H

void abs_turn_speed_ctrl( int speed, e_turn_method turn_method, e_direction dir)
{
	//-------------------------
	// swing turn
	//-------------------------
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

	//-------------------------
	// point turn
	//-------------------------
	else
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
}
#endif /*ABS_TURN_SPEED_CTRL_H*/
