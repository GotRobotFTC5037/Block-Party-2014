/**
*
*  @file abs_control_light_sensor.h
*
*  @brief  Enter a description of what this function does
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_CONTROL_LIGHT_SENSOR_H
#define ABS_CONTROL_LIGHT_SENSOR_H

void abs_control_light_sensor(e_light_sensor_status status)
{
	if(status == ACTIVE)
	{
#if EOPD_ACTIVE == 0
		LSsetActive(LEGOLS);
#endif
		//LSsetActive(LEGOLS);
	}
	else
	{
#if EOPD_ACTIVE == 0
		LSsetInactive(LEGOLS);
		//LSsetInactive(LEGOLS);
#endif
	}
}

#endif /* !TEMPLATE_H */
