/**
*
*  @file abs_calibrate_optical.h
*
*  @brief  Calibrates the optical sensor
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_CALIBRATE_OPTICAL_H
#define ABS_CALIBRATE_OPTICAL_H

#include "global_variables.h"
#include "abs_log.h"
#include "abs_control_light_sensor.h"
#include "math_utils.h"

task abs_calibrate_optical()
{
	servo[optical_servo] = OPTICAL_SERVO_DOWN;
	wait1Msec(1000);
#if EOPD_ACTIVE == 0
	abs_control_light_sensor(ACTIVE);
#endif

	long calibration_start = nPgmTime;
        int i;
        int avg_optical_reading = 0;
        int min_optical_reading = DEFAULT_CALIBRATED_OPTICAL_THRESHOLD;
        int max_optical_reading = 0;

	for(i=0; nPgmTime < OPTICAL_SENSOR_CALIBRATION_TIME + calibration_start; i++)
        {
          int optical_reading = g_optical_sensor;

          min_optical_reading = min(min_optical_reading, optical_reading);
          max_optical_reading = max(min_optical_reading, optical_reading);
          avg_optical_reading = running_avg(avg_optical_reading, i, optical_reading);

	  wait1Msec(OPTICAL_CALIBRATION_SAMPLE_RATE);
        }

	abs_log(__FILE__ ,"Captured Data",i,avg_optical_reading,min_optical_reading,max_optical_reading);

	//Tells the robot how bright the white line should be based on how black black is
	if(avg_optical_reading == 0)
	{
		g_calibrated_optical_threshold_val = DEFAULT_CALIBRATED_OPTICAL_THRESHOLD;
		abs_log(__FILE__ ,"Optical calibration failed",g_calibrated_optical_threshold_val,avg_optical_reading,g_optical_delta_value,0);
	}
	else
	{
		g_calibrated_optical_threshold_val = avg_optical_reading + g_optical_delta_value;
		abs_log(__FILE__ ,"Optical calibration worked",g_calibrated_optical_threshold_val,avg_optical_reading,g_optical_delta_value,0);
	}

#if EOPD_ACTIVE == 0
	abs_control_light_sensor(INACTIVE);
#endif
	wait1Msec(1000);
	servo[optical_servo] = OPTICAL_SERVO_UP;
}

#endif /* !TEMPLATE_H */
