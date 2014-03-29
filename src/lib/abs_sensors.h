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
#include "abs_set_heading.h"

#include "abs_log_multivalue.h"

#define DRIFT_COMPENSATION_FACTOR 0.0070  // gyro units per second

task abs_sensors()
{
	g_prev_time = nPgmTime;
	int raw_gyro1 = 0;
	int raw_gyro2 = 0;

	while(true)
	{
		//-------------------------
		// Light Sensor
		//-------------------------
		//g_light_sensor = LSvalNorm(LEGOLS);
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
		int drift_compensation = 0;
		static int last_drift_compensation_time = g_curr_time;

		//if(DRIFT_COMPENSATION_FACTOR * ((g_curr_time - last_drift_compensation_time)/1000) >= 1)
		//{
		last_drift_compensation_time = g_curr_time;
		drift_compensation = DRIFT_COMPENSATION_FACTOR * ((g_curr_time - last_drift_compensation_time)/1000);
		//}

		raw_gyro1 = abs_get_gyro_sensor_val(RAW,GYRO1);
		// gyro 1
		#if CLASSIC_GYRO_READ == 0
		abs_set_heading(RELATIVE, GYRO1, g_rel_heading1 + ((raw_gyro1 - (g_gyro1_drift+(g_delta_drift*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000) + drift_compensation);
		abs_set_heading(CONSTANT, GYRO1, g_const_heading1 + ((raw_gyro1 - (g_gyro1_drift+(g_delta_drift*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000) + drift_compensation);
		#else
		abs_set_heading(RELATIVE, GYRO1, g_rel_heading1 + ((raw_gyro1 - g_gyro1_drift) * (float)(g_curr_time-g_prev_time)/1000));
		abs_set_heading(CONSTANT, GYRO1, g_const_heading1 + ((raw_gyro1 - g_gyro1_drift) * (float)(g_curr_time-g_prev_time)/1000));
		abs_log_multivalue(LIST1, g_rel_heading1);
		#endif

		// gyro 2
		raw_gyro2 = abs_get_gyro_sensor_val(RAW,GYRO2);
		abs_set_heading(RELATIVE, GYRO2, g_rel_heading2 + ((raw_gyro2 - (g_gyro2_drift+(g_delta_drift2*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000) + drift_compensation);
		abs_set_heading(CONSTANT, GYRO2, g_const_heading2 + ((raw_gyro2 - (g_gyro2_drift+(g_delta_drift2*(float)(g_curr_time-g_prev_time)))) * (float)(g_curr_time-g_prev_time)/1000) + drift_compensation);
		//abs_log_multivalue(LIST2, g_rel_heading2);

		//used gyro
		if(g_gyro_use==GYRO1)
		{
			abs_set_heading(RELATIVE, SELECTED_GYRO, g_rel_heading1);
			abs_set_heading(CONSTANT, SELECTED_GYRO, g_const_heading1);
		}
		else
		{
			abs_set_heading(RELATIVE, SELECTED_GYRO, g_rel_heading2);
			abs_set_heading(CONSTANT, SELECTED_GYRO, g_const_heading2);
		}

		g_prev_time = g_curr_time;

		g_recont_heading = /*g_const_heading*/g_const_heading_use % 360;
		if(g_recont_heading<0) g_recont_heading += 360;

		//-------------------------
		// HiTechnic accelermoeter
		//-------------------------

		//HTACreadAllAxes(HTAC, g_x_axis, g_y_axis, g_z_axis);
		//g_accelermoeter_sensor = g_x_axis;

		//if(g_sensor_reference_drive == true)
		//{
		//	g_accelermoeter_reads++;
		//	g_accelermoeter_array[g_accelermoeter_reads%50]=g_accelermoeter_sensor;
		//	for(int i=0;i<30;i++)
		//	{
		//		g_accelermoeter_total_value = g_accelermoeter_array[i];
		//	}
		//	g_accelermoeter_average = g_accelermoeter_total_value/50;
		//}
		//else
		//{
		//	g_accelermoeter_reads = 0;
		//	g_accelermoeter_total_value = 0;
		//	g_accelermoeter_average = 0;
		//	memset(g_accelermoeter_array,0,30);
		//}
		//-------------------------
		// HiTechnic angle sensor
		//-------------------------
		g_angle_sensor = HTANGreadAccumulatedAngle(angle_sensor);
		//-------------------------
		// EOPD
		//-------------------------
		HTEOPDsetLongRange(HTEOPD);
		g_EOPD_sensor = HTEOPDreadRaw(HTEOPD);
	}
}
#endif
