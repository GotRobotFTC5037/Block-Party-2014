/**
 *
 *  @file abs_gyro_cal.h
 *
 *  @brief A header file that allows you to calculate the input comming from the gyro
 *
 *  @param caltime how long does the gyro calibrate for
 *
 *  @return The drift
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */
#ifndef ABS_GYRO_CAL_H
#define ABS_GYRO_CAL_H

/** macros */
//====================================
// Gyro Calibration helper function
//====================================
float abs_gyro_cal(long caltime)
{
	long highest = -1000, lowest = 10000;
	float average = 0;
	long starttime = nPgmTime;
	long samples=0;
	long data;
	while (nPgmTime < starttime+caltime)			// loop for the requested number of seconds
	{
		samples +=1;														// count the number of iterations for averaging
		data = HTGYROreadRot(HTGYRO);						// get a new reading from the GYRO
		average += (float)data;									// add in the new value to the average
		if (highest < data) highest = data;			// adjust the highest value if necessary
			if (lowest> data) lowest = data;				// likewise for the lowest value
	}
	//gyro_noise=abs(highest-lowest);						// save the spread in the data for diagnostic display
	return average/samples;										// and return the average drift
}

#endif /* !ABS_GYRO_CAL_H */
