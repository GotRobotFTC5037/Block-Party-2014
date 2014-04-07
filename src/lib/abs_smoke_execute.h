/**
*
*  @file abs_smoke_execute.h
*
*  @brief executes commands sent in smoke test
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_SMOKE_EXECUTE_H
#define ABS_SMOKE_EXECUTE_H

#include "abs_get_angle_sensor_val.h"
#include "lib/abs_smoke_test_view.h"

void abs_smoke_execute(int test_num)
{
	while(nNxtButtonPressed!=kEnterButton)
	{
		switch(test_num)
		{
		case 1:
			if(nNxtButtonPressed==kLeftButton)
			{
				motor[block_lift_motor] = g_block_speed_down;
				motor[block_lift_motor2] = g_block_speed_down;
				abs_smoke_test_view(test_num,g_block_speed_down,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				motor[block_lift_motor] = g_block_speed_up;
				motor[block_lift_motor2] = g_block_speed_up;
				abs_smoke_test_view(test_num,g_block_speed_up,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			abs_smoke_test_view(test_num,0,0);
			motor[block_lift_motor] = 0;
			motor[block_lift_motor2] = 0;
			break;
		case 2:
			if(nNxtButtonPressed==kLeftButton)
			{
				motor[sky_hook] = g_robot_lift_down;
				abs_smoke_test_view(test_num,g_robot_lift_down,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				motor[sky_hook] = g_robot_lift_up;
				abs_smoke_test_view(test_num,g_robot_lift_up,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			abs_smoke_test_view(test_num,0,0);
			motor[sky_hook] = 0;
			break;
		case 3:
			if(nNxtButtonPressed==kLeftButton)
			{
				motor[right_motor] = -80;
				motor[left_motor] = -80;
				abs_smoke_test_view(test_num,-80,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				motor[right_motor] = 80;
				motor[left_motor] = 80;
				abs_smoke_test_view(test_num,80,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			abs_smoke_test_view(test_num,0,0);
			motor[right_motor] = 0;
			motor[left_motor] = 0;
			break;
		case 4:
			static int left_grabber = 0;
			static int right_grabber = 0;
			static int grabbers_pos = 1;
			if(nNxtButtonPressed==kLeftButton&&grabbers_pos>1)
			{
				grabbers_pos--;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton&&grabbers_pos<3)
			{
				grabbers_pos++;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			switch(grabbers_pos)
			{
			case 1:
				left_grabber = GRABBER_LEFT_CLOSE;
				right_grabber = GRABBER_RIGHT_CLOSE;
				break;
			case 2:
				left_grabber = GRABBER_LEFT_MID;
				right_grabber = GRABBER_RIGHT_MID;
				break;
			case 3:
				left_grabber = GRABBER_LEFT_OPEN;
				right_grabber = GRABBER_RIGHT_OPEN;
				break;
			}
			servo[grabber_left] = left_grabber;
			servo[grabber_right] = right_grabber;
			abs_smoke_test_view(test_num,left_grabber,right_grabber);
			break;
		case 5:
			static int abdd_pos = 1;
			if(nNxtButtonPressed==kLeftButton&&abdd_pos>1)
			{
				abdd_pos--;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton&&abdd_pos<2)
			{
				abdd_pos++;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			if(abdd_pos==1){servo[abdd] = g_abdd_up;abs_smoke_test_view(test_num,g_abdd_up,0);}
			else {servo[abdd] = g_abdd_down;abs_smoke_test_view(test_num,g_abdd_down,0);}
			break;
		case 6:
			if(nNxtButtonPressed==kLeftButton)
			{
				servo[roger_slide] = 0;
				abs_smoke_test_view(test_num,0,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				servo[roger_slide] = 255;
				abs_smoke_test_view(test_num,255,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			abs_smoke_test_view(test_num,127,0);
			servo[roger_slide] = 127;
			break;
		case 7:
			if(nNxtButtonPressed==kLeftButton)
			{
				motor[jolly_roger] = g_flag_speed_down;
				abs_smoke_test_view(test_num,g_flag_speed_down,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				motor[jolly_roger] = g_flag_speed_up;
				abs_smoke_test_view(test_num,g_flag_speed_up,0);
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			abs_smoke_test_view(test_num,0,0);
			motor[jolly_roger] = 0;
			break;
		case 8:
			static int optical_servo_pos = OPTICAL_SERVO_UP;
			if(nNxtButtonPressed==kLeftButton)
			{
				optical_servo_pos = OPTICAL_SERVO_DOWN;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kLeftButton){}
			}
			else if(nNxtButtonPressed==kRightButton)
			{
				optical_servo_pos = OPTICAL_SERVO_UP;
				PlaySoundFile("! Click.rso");
				while(nNxtButtonPressed==kRightButton){}
			}
			servo[optical_servo] = optical_servo_pos;
			abs_smoke_test_view(test_num,optical_servo_pos,0);
			break;
		case 9:
			//abs_smoke_test_view(test_num,g_angle_sensor,g_angle_sensor/INT_ANGLE_SENSOR_CIRCUMFERENCE);
			break;
		default: abs_cscreen("ERROR   ","Test 2 B","added   "); break;
		}
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed==kEnterButton){}
}

#endif /* !ABS_SMOKE_EXECUTE_H */
