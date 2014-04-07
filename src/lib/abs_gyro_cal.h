/**
 *
 *  @file abs_gyro_cal.h
 *
 *  @brief A header file that allows you to calculate the input comming from the gyro
 *
 *  @param caltime Tells the robot how long to calibrate the gyro
 *
 *  @return The drift
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */
#ifndef ABS_GYRO_CAL_H
#define ABS_GYRO_CAL_H

#include "abs_dlog.h"

float abs_gyro_cal(long caltime)
{
	long highest = -1000, lowest = 10000;
	float average = 0;
	g_start_time = nPgmTime;
	long samples=0;
	long data;

	g_original_gyro_val = HTGYROreadRot(HTGYRO);		// get initial gyro reading

	while (nPgmTime < g_start_time+(caltime*1000))		// loop for the requested number of seconds
	{
		samples +=1;					// count the number of iterations for averaging
		data = HTGYROreadRot(HTGYRO);			// get a new reading from the GYRO
		average += (float)data;				// add in the new value to the average
		if (highest < data) highest = data;		// adjust the highest value if necessary
			if (lowest> data) lowest = data;	// likewise for the lowest value
	}
	//g_gyro_noise=abs(highest-lowest);			// save the spread in the data for diagnostic display
	g_gyro_noise=abs(highest-lowest);

	g_original_gyro_val = (g_original_gyro_val - (average/samples)) * (float)(nPgmTime - g_start_time) / 1000;
        abs_dlog(__FILE__,"Original Gyro Reading","value",g_original_gyro_val);

	return average/samples;					// and return the average drift
}

#endif /* !ABS_GYRO_CAL_H */
