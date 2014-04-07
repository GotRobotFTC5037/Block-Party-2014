/**
*
*  @file abs_get_angle_sensor_val.h
*
*  @brief  Enter a description of what this function does
*
*  @param
*
*  @return
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_GET_ANGLE_SENSOR_VAL_H
#define ABS_GET_ANGLE_SENSOR_VAL_H

long abs_get_angle_sensor_val(e_angle_val_type angle_val)
{
	if(angle_val == RELATIVE_ASU)
	{
		return abs(HTANGreadAccumulatedAngle(angle_sensor) - g_angle_sensor_val);
	}
	else if(angle_val == RAW_ASU)
	{
		return abs(HTANGreadAccumulatedAngle(angle_sensor));
	}
	else if(angle_val == RELATIVE_BPU)
	{
		return abs(HTANGreadAccumulatedAngle(angle_sensor) - g_angle_sensor_val)/INT_ANGLE_SENSOR_CIRCUMFERENCE;
	}
	else
	{
		return abs(HTANGreadAccumulatedAngle(angle_sensor))/INT_ANGLE_SENSOR_CIRCUMFERENCE;
	}
}

#endif /* !ABS_GET_ANGLE_SENSOR_VAL_H */
