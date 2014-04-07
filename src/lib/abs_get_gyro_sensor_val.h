/**
*
*  @file abs_get_gyro_sensor_val.h
*
*  @brief  Enter a description of what this function does
*
*  @param
*
*  @return
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_GET_GYRO_SENSOR_VAL_H
#define ABS_GET_GYRO_SENSOR_VAL_H

#include "math_utils.h"

int abs_get_gyro_sensor_val(e_gyro_val_type gyro_val)
{
	static int last_gyro_read_time = 0;
	static int last_gyro_read_val = 0;

	int current_time = nPgmTime;
	int last_val;
	int delta_time;
	if(g_gyro_ran == true)
	{
		last_val = last_gyro_read_val;
		delta_time = last_gyro_read_time - current_time;
	}

	last_gyro_read_time = current_time;

	if(gyro_val == RAW)
	{
		last_gyro_read_val = HTGYROreadRot(HTGYRO);
	}
	else
	{
		last_gyro_read_val = HTGYROreadRot(HTGYRO) - g_original_gyro_val;
	}

#if DEBUG_MODE == 1

	static bool queue_empty = true;
	static int current_index = 0;
	if(current_index == GYRO_VALUE_QUEUE_SIZE) { current_index = 0; }

	/**
	* if the queue is empty, initialize all values to the first reading
	* otherwise, insert the value to the next point in the queue
	*/
	if(queue_empty)
	{
		queue_empty = false;
		for(int i=0; i<GYRO_VALUE_QUEUE_SIZE; i++)
		{
			g_gyro_values[i] = last_gyro_read_val;
		}
	}
	else
	{
		g_gyro_values[current_index] = last_gyro_read_val;
	}

	current_index++;

	if(current_index%GYRO_VALUE_QUEUE_SIZE==0)
	{
		for(int i=0;i<GYRO_VALUE_QUEUE_SIZE;i++)
		{
			abs_dlog(__FILE__, "Gyro Queue ", "Entry %d = ", i, "%d", g_gyro_values[i]);
		}
		abs_dlog(__FILE__, "Gyro Queue ", "middle_value_avg %d = ", middle_value_avg());
	}
#endif

	if(g_gyro_ran == true)
	{
		int delta_val = abs(last_gyro_read_val - last_val);

		if(delta_val / delta_time > MAX_TURN_RATE)
		{
			g_good_gyro = false;
		}
	}

	if(g_gyro_ran == false) g_gyro_ran = true;

	return last_gyro_read_val;
}

#endif /* !ABS_GET_GYRO_SENSOR_VAL_H */
