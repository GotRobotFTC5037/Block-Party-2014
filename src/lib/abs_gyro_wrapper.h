/**
*
*  @file abs_gyro_wrapper.h
*
*  @brief
*
*  @param
*
*  @return
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_GYRO_WRAPPER_H
#define ABS_GYRO_WRAPPER_H

#include "abs_gyro_cal.h"
#include "abs_dlog.h"

#define REPEAT 4

float abs_gyro_wrapper()
{
	int delta_total = 0;
	int drift_old = 0;
	int delta_gyro_array [REPEAT-1];
	memset(delta_gyro_array,0,REPEAT-1);
	int drift_gyro_array [REPEAT];
	memset(drift_gyro_array,0,REPEAT);

	for(int i=0;i<REPEAT;i++)
	{
	  drift_gyro_array[i] = abs_gyro_cal(g_gyro_cal_time);
//	  delta_gyro_array[i] = drift-drift_old;
	//  drift_old = drift;
	}
	for(int i=0;i<REPEAT-1;i++)
	{
		delta_gyro_array[i] = drift_gyro_array[i+1] - drift_gyro_array[i];
		delta_total += delta_gyro_array[i];
	}

	g_delta_drift = delta_total/(REPEAT-1);

	abs_dlog(__FILE__ ,"Program start"," dr1: ", drift_gyro_array[0]," dr2: %d ", drift_gyro_array[1]," dr3: %d ", drift_gyro_array[2]," dr4: %d ", drift_gyro_array[3]);
	abs_dlog(__FILE__ ,"Program start"," d1: ", delta_gyro_array[0]," d2: %f ", delta_gyro_array[1]," d3: %f ", delta_gyro_array[2]);
	abs_dlog(__FILE__ ,"Program start"," Drift: ", drift_gyro_array[REPEAT-1], " delta: ", g_delta_drift);

	return drift_gyro_array[REPEAT-1];
}
#endif /* !ABS_GYRO_WRAPPER_H */
