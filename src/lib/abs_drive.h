/**
*
*  @file abs_drive.h
*
*  @brief it allows the robot to drive forword and backward
*
*  @param dir Tells the robot what direction to go
*
*  @param dist_method tells the robot how it should know when to stop
*
*  @param dist tells the robot how far to go
*
*  @param speed tells the robot how fast to go
*
*  @param stop_at_end tells the robot if it should stop when it gets to were it needs to go or not
*
*  @return returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_DRIVE_H
#define ABS_DRIVE_H

#include "abs_gyro_drive.h"

void abs_drive(e_drive_direction dir, e_move_stopping_method dist_method, int dist, int speed, bool stop_at_end, e_drive_type drive_type)
{
	if(dist_method == E_IR_DETECT || dist_method == E_IR_DETECT2) dl_IR = true;
	else dl_IR = false;
	int i = 0;
	dl_step = dl_step+1;

	dl_robot_action_state = dl_gyro_move;
	dl_speed = speed;
	nMotorEncoder(right_motor)= 0;
	g_rel_heading = 0;
	dl_speed = speed;
	dl_dist = dist;

	if(stop_at_end == true)	dl_robot_action_detail = dl_move_stop;
	else dl_robot_action_detail = dl_move_no_stop;

	//------------------------
	// time stopping method
	//------------------------
	if(dist_method == E_TIME)
	{
		ClearTimer(T1);
		while(time1[T1] < dist)
		{
			if(drive_type == GYRO)
			{
				abs_gyro_drive(speed,dir);
				dl_cur_dist = time1[T1];
			}

			/** No gyro correction*/
			else
			{
				if(dir == FORWARD)
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}

			}
		}
	}
	//------------------------
	// encoder stopping method
	//------------------------
	else if(dist_method == E_DEGREES)
	{
		while(i<5)
		{
			if(abs(nMotorEncoder(right_motor)) > distance_to_encoder_derees(dist)) i++;
			if(drive_type == GYRO)
			{
				abs_gyro_drive(speed,dir);
				dl_cur_dist = nMotorEncoder(right_motor);
			}

			/** No gyro correction*/
			else
			{
				if(dir == FORWARD)
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
		}
	}
	//------------------------
	// IR stopping method
	//------------------------
	else if(dist_method == E_IR_DETECT)
	{
		if(dir == FORWARD)
		{
			while(abs(HTANGreadAccumulatedAngle(angle_sensor)) < (150*INT_ANGLE_SENSOR_CIRCUMFERENCE))
			{
				dl_cur_dist = g_bearing_ac2;
				if(abs(HTANGreadAccumulatedAngle(angle_sensor)) < (100*INT_ANGLE_SENSOR_CIRCUMFERENCE))
				{
					if(!((g_bearing_ac2 >= dist - 1) || (g_bearing_ac2 == 0))) break;
				}
				else
				{
					if(!((g_bearing_ac2 >= dist) || (g_bearing_ac2 == 0))) break;
				}
				if(drive_type == GYRO)
				{
					abs_gyro_drive(speed,dir);
				}

				/** No gyro correction*/
				else
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
			}
			//g_screen_state = S_TIME_SHOW;
			g_debug_time_1 = nPgmTime;
		}
		else if(dir == BACKWARD)
		{
			while(abs(HTANGreadAccumulatedAngle(angle_sensor)) < (150*INT_ANGLE_SENSOR_CIRCUMFERENCE))
			{
				if(abs(HTANGreadAccumulatedAngle(angle_sensor)) < (100*INT_ANGLE_SENSOR_CIRCUMFERENCE))
				{
					if(!((g_bearing_ac1 <= dist + 1) || (g_bearing_ac1 == 0))) break;
				}
				else
				{
					if(!((g_bearing_ac1 <= dist) || (g_bearing_ac1 == 0))) break;
				}

				/** No gyro correction*/
				if(drive_type == GYRO)
				{
					abs_gyro_drive(speed,dir);
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
		}
	}
	//------------------------
	// IR stopping method 2
	//------------------------
	else if(dist_method == E_IR_DETECT2)
	{
		if(dir == FORWARD)
		{
			while(g_ir_bearing2 > dist)
			{
				if(drive_type == GYRO)
				{
					abs_gyro_drive(speed,dir);
				}
				/** No gyro correction*/
				else
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
			}
		}
		else
		{
			while(g_ir_bearing2 < dist)
			{
				if(drive_type == GYRO)
				{
					abs_gyro_drive(speed,dir);
				}
				/** No gyro correction*/
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
		}
	}

	//------------------------
	// accelermeoter sensor stopping method
	//------------------------
	else if(dist_method == E_TILT)
	{
		dl_cur_dist = g_accelermoeter_average;
		int j = 0;
		g_sensor_reference_drive = true;
		while(j<30)
		{
			if(drive_type == GYRO)
			{
				abs_gyro_drive(speed,dir);
			}

			/** No gyro correction*/
			else
			{
				if(dir == FORWARD)
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
			if(g_accelermoeter_average > dist) j++;
		}
		g_sensor_reference_drive = false;
	}
	//------------------------
	// angle sensor stopping method
	//------------------------
	else if(dist_method == E_ANGLE)
	{
		HTANGresetAccumulatedAngle(angle_sensor);
		while(abs(HTANGreadAccumulatedAngle(angle_sensor)) < (dist*INT_ANGLE_SENSOR_CIRCUMFERENCE))
		{
			if(drive_type == GYRO)
			{
				dl_cur_dist = HTANGreadAccumulatedAngle(angle_sensor);
				abs_gyro_drive(speed,dir);
			}

			/** No gyro correction*/
			else
			{
				if(dir == FORWARD)
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
		}
	}
	//--------------
	//   Light
	//--------------
	else
	{
		LSsetActive(LEGOLS);
		servo[light_sensor] = LIGHT_SERVO_DOWN;
		while(g_light_sensor <= 30)
		{
			dl_cur_dist= g_light_sensor;
			if(drive_type == GYRO)
			{
				abs_gyro_drive(speed,dir);
			}

			/** No gyro correction*/
			else
			{
				if(dir == FORWARD)
				{
					motor[left_motor] = speed;
					motor[right_motor] = speed;
				}
				else
				{
					motor[left_motor] = -speed;
					motor[right_motor] = -speed;
				}
			}
		}
	}
	if(g_end_point == 3) g_dist_backwards = (abs(HTANGreadAccumulatedAngle(angle_sensor))/18)-(5);
	else if(g_end_point == 2) g_dist_backwards = 190-(abs(HTANGreadAccumulatedAngle(angle_sensor))/18);

	servo[light_sensor] = LIGHT_SERVO_UP;
	LSsetInactive(LEGOLS);

	//------------------------
	// Stop
	//------------------------
	if(stop_at_end)
	{
		motor[left_motor] = 0;
		motor[right_motor] = 0;
	}
	g_debug_time_2 = nPgmTime;
}

#endif /* !ABS_DRIVE_H */
