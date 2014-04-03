/**
*
*  @file abs_s6_mission_execute.h
*
*  @brief runs the missions from the starting point S1
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_S6_MISSION_EXECUTE_H
#define ABS_S6_MISSION_EXECUTE_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_stop_robot.h"
#include "abs_end_ramp.h"
#include "abs_dlog.h"
#include "abs_get_angle_sensor_val.h"
#include "abs_stay_on_ramp.h"

void abs_s6_mission_execute()
{
	switch(g_mission_number)
	{
	case 0:
		abs_drive(FORWARD, E_ANGLE, 240, 40, true, GYRO);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 80, 40);
		abs_drive(FORWARD, E_ANGLE, 100, 40, true, GYRO);
		break;

	case 1:
		break;

		default:
		g_end_point = 1;
		break;
	}
}

#endif /* !ABS_S6_MISSION_EXICUTE_H */
