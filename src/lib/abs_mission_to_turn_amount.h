/**
*
*  @file abs_mission_to_turn_amount.h
*
*  @brief  Enter a description of what this function does
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_MISSION_TO_TURN_AMOUNT_H
#define ABS_MISSION_TO_TURN_AMOUNT_H

int abs_mission_to_turn_amount(int starting_point, int ramp_position, bool good_gyro)
{
	if(good_gyro)
	{
		switch (starting_point)
		{
		case 1:
		case 2:
			if(ramp_position == 2)
			{
				return 277;
			}
			else
			{
				return 268;
			}
		case 3:
			return 315;
		case 4:
			return 45;
		default:
			return 0;
		}
	}
	else
	{
		if(ramp_position == 2)
		{
			return 83;
		}
		else
		{
			return 88;
		}
	}
}
#endif /* !TEMPLATE_H */
