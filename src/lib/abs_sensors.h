/**
*
*  @file abs_sensors.h
*
*  @brief A header file that handles the sensors
*
*  @param None n/a
*
*  @return returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_SENSOR_H
#define ABS_SENSOR_H

#include "math_utils.h"
#include "abs_get_gyro_sensor_val.h"

task abs_sensors()
{
	g_prev_time = nPgmTime;

	while(true)
	{
		//-------------------------
		// HiTechnic IR Sensor
		//-------------------------
		g_bearing_ac1 = HTIRS2readACDir(HTIRS2);				// Read the IR bearing from the sensor
		g_curr_dir1 = (float) g_bearing_ac1;

		HTIRS2readAllACStrength(HTIRS2, g_acs1[0], g_acs1[1], g_acs1[2], g_acs1[3], g_acs1[4]);
		//-----------------------------------
		// code for the peaks of IR sensor
		//-----------------------------------
		if (g_bearing_ac1!=0)								// we have a valid IR signal
		{
			int maximum = -1;
			int peak = 0, offset=0;
			for (int i=0;i<5;i++)	// scan array to find the peak entry
			{	if (g_acs1[i]>maximum)
				{
					peak = i;
					maximum = g_acs1[i];
				}
			}
			offset=0;
			if ((peak < 4) && (peak>0) && (g_acs1[peak] != 0))  // we are not working with extreme value
			{
				if (g_acs1[peak-1]!=g_acs1[peak+1]) // if the values either side of the peak are identical then peak is peak
				{
					if (g_acs1[peak-1]>g_acs1[peak+1])	// otherwise decide which side has higher signal
					{
						offset = -25*(1-(float)(g_acs1[peak]-g_acs1[peak-1])/		// calculate the bias away from the peak
						max(g_acs1[peak], g_acs1[peak-1]));
					}
					else
					{
						offset = 25*(1-(float)(g_acs1[peak]-g_acs1[peak+1])/
						max(g_acs1[peak], g_acs1[peak+1]));
					}
				}
			}
			g_ir_bearing1 = (float)((peak-2)*50) + offset;		// direction is the total of the peak bias plus the adjacent bias
			//nxtDisplayBigTextLine(3, "%2d", g_ir_bearing1);
		}
		//-------------------------
		// HiTechnic IR Sensor 2
		//-------------------------
		g_bearing_ac2 = HTIRS2readACDir(HTIRS2_2);				// Read the IR bearing from the sensor
		g_curr_dir2 = (float) g_bearing_ac2;

		HTIRS2readAllACStrength(HTIRS2_2, g_acs2[0], g_acs2[1], g_acs2[2], g_acs2[3], g_acs2[4]);
		//-----------------------------------
		// code for the peaks of IR sensor 2
		//-----------------------------------
		if (g_bearing_ac2!=0)								// we have a valid IR signal
		{
			int maximum = -1;
			int peak = 0, offset=0;
			for (int i=0;i<5;i++)	// scan array to find the peak entry
			{	if (g_acs2[i]>maximum)
				{
					peak = i;
					maximum = g_acs2[i];
				}
			}
			offset=0;
			if ((peak < 4) && (peak>0) && (g_acs2[peak] != 0))  // we are not working with extreme value
			{
				if (g_acs2[peak-1]!=g_acs2[peak+1]) // if the values either side of the peak are identical then peak is peak
				{
					if (g_acs2[peak-1]>g_acs2[peak+1])	// otherwise decide which side has higher signal
					{
						offset = -25*(1-(float)(g_acs2[peak]-g_acs2[peak-1])/		// calculate the bias away from the peak
						max(g_acs2[peak], g_acs2[peak-1]));
					}
					else
					{
						offset = 25*(1-(float)(g_acs2[peak]-g_acs2[peak+1])/
						max(g_acs2[peak], g_acs2[peak+1]));
					}
				}
			}
			g_ir_bearing2 = (float)((peak-2)*50) + offset;		// direction is the total of the peak bias plus the adjacent bias
			//nxtDisplayBigTextLine(3, "%2d", g_ir_bearing1);
		}
		//-------------------------
		// HiTechnic Gyro
		//-------------------------

		g_curr_time=nPgmTime;
		g_raw_gyro = abs_get_gyro_sensor_val(RAW);
		g_sacred_const_heading += (g_raw_gyro - (g_drift+(g_delta_drift*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000;
		g_rel_heading += (g_raw_gyro - (g_drift+(g_delta_drift*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000;

		g_const_heading += (g_raw_gyro - (g_drift+(g_delta_drift*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000;

		//abs_dlog(__FILE__ ,"heading"," g_const_heading: %d ", g_const_heading," g_rel_heading: %d ", g_rel_heading);
		//wait1Msec(100);
		g_prev_time = g_curr_time;

		g_recont_heading = g_const_heading % 360;
		if(g_recont_heading<0) g_recont_heading += 360;

		//-------------------------
		// HiTechnic accelermoeter
		//-------------------------

		HTACreadAllAxes(HTAC, g_x_axis, g_y_axis, g_z_axis);
		g_accelermoeter_sensor = g_x_axis;

		if(g_sensor_reference_drive == true)
		{
			g_accelermoeter_reads++;
			g_accelermoeter_array[g_accelermoeter_reads%50]=g_accelermoeter_sensor;
			for(int i=0;i<30;i++)
			{
				g_accelermoeter_total_value = g_accelermoeter_array[i];
			}
			g_accelermoeter_average = g_accelermoeter_total_value/50;
		}
		else
		{
			g_accelermoeter_reads = 0;
			g_accelermoeter_total_value = 0;
			g_accelermoeter_average = 0;
			memset(g_accelermoeter_array,0,30);
		}
		//-------------------------
		// EOPD Sensor
		//-------------------------
#if EOPD_ACTIVE == 1
		HTEOPDsetLongRange(HTEOPD);
		g_EOPD_sensor = HTEOPDreadRaw(HTEOPD);
		g_optical_sensor = g_EOPD_sensor;
#else
		//-------------------------
		// Light Sensor
		//-------------------------
		g_light_sensor = LSvalNorm(LEGOLS);
		g_optical_sensor = g_light_sensor;
#endif
	}
}
#endif
