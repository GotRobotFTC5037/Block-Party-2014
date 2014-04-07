/**
*
*  @file abs_stay_on_ramp.h
*
*  @brief  Allows the robot to stay on the ramp even of someone pushes us
*
*  @param
*
*  @return
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_STAY_ON_RAMP_H
#define ABS_STAY_ON_RAMP_H

#include "math_utils.h"
#include "global_variables.h"

void abs_stay_on_ramp()
{
	int stop_location = abs_get_angle_sensor_val(RAW_BPU);
	while(true)
	{
		motor[right_motor] = safe_motor_speed(stop_location - abs_get_angle_sensor_val(RAW_BPU));
		motor[left_motor] = safe_motor_speed(stop_location - abs_get_angle_sensor_val(RAW_BPU));
		wait1Msec(STAY_ON_RAMP_WAIT_TIME);
	}
}

#endif /* !STAY_ON_RAMP_H */
