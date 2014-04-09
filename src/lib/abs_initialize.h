/**
*
*  @file abs_initialize.h
*
*  @brief A header file that handles the initialization when we start the game
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_INITIALIZE_H
#define ABS_INITIALIZE_H

#include "abs_gyro_wrapper.h"
#include "abs_sensors.h"
#include "abs_dlog.h"
#include "abs_reset_angle_sensor.h"
#include "abs_calibrate_optical.h"
#include "abs_selection_program.h"
#include "abs_control_light_sensor.h"

void abs_initialize()
{
	disableDiagnosticsDisplay();
	servoChangeRate[abdd] = 3;
	servo[roger_slide] = 127;
	servo[abdd] = g_abdd_down;
	servo[grabber_left] = GRABBER_LEFT_CLOSE;
	servo[grabber_right] = GRABBER_RIGHT_CLOSE;
	servo[optical_servo] = OPTICAL_SERVO_UP;
	abs_control_light_sensor(INACTIVE);
	memset(g_input_array,0,INPUT_ARRAY_SIZE);
	abs_selection_program();
	PlaySoundFile("! Click.rso");
	abs_cscreen("Gyros   ","Calbrtng","  lol   ");
	g_drift = abs_gyro_wrapper();

	if(!HTACreadAllAxes(HTAC, g_x_axis, g_y_axis, g_z_axis))
	{
		g_error = ERR_ACCELERMOETER;
		g_error_type = ERROR_NONLETHAL;
	}
	if(g_gyro_noise>10)
	{
		g_error = ERR_GYRO_CAL;
		g_error = ERROR_LETHAL;
	}
	if(HTSMUXreadPowerStatus(SENSOR_MUX))
	{
		g_error = ERR_SENSOR_MUX;
		g_error_type = ERROR_NONLETHAL;
	}
	if(HTSMUXreadPowerStatus(GYRO_MUX))
	{
		g_error = ERR_GYRO_MUX;
		g_error = ERROR_LETHAL;
	}

	if(g_error != 0)
	{
		switch(g_error)
		{
		case ERR_ACCELERMOETER: abs_cscreen("ERROR N ","Accel   ","        "); break;
		case ERR_GYRO_CAL: abs_cscreen("ERROR L ","Gryo1   ","cal fail"); break;
		case ERR_SENSOR_MUX: abs_cscreen("ERROR L ","SensrMux","pwr fail"); break;
		case ERR_GYRO_MUX: abs_cscreen("ERROR L ","Gyro1Mux","pwr fail"); break;
		}
		while(true)
		{
			g_gyro_true = true;
			PlayTone (250,25);
			wait1Msec(500);
			if(nNxtButtonPressed == kEnterButton && g_error_type == ERROR_NONLETHAL)break;
		}
	}
	LogData=true;

	abs_cscreen("Program ","Ready   ","        "); //set the screen to show the program feedback before the auto starts
	if(g_auto_selection_ramp_continue_options == SUB_SELECTION_RAMP_CONTINUED)
		nxtDisplayBigTextLine(5, "%1d%1d%1d%1d%1d%1d%1d%1d Y ",g_input_array[1],g_input_array[2],g_input_array[3],g_input_array[4],g_input_array[5]);
	else
		nxtDisplayBigTextLine(5, "%1d%1d%1d%1d%1d%1d%1d%1d N ",g_input_array[1],g_input_array[2],g_input_array[3],g_input_array[4],g_input_array[5]);
	StartTask(abs_sensors);

	abs_reset_angle_sensor_val(HARD_RESET);

	PlayTone(700, 100);

#if WAIT == 0
	waitForStart();

#else
while(nNxtButtonPressed == kEnterButton){}
if(nNxtButtonPressed != kEnterButton) wait1Msec(5000);
#endif

	abs_dlog(__FILE__ ,"auto start","timestamp",nPgmTime);

	eraseDisplay();
	g_start_time = nPgmTime;

	//while(/*time1[T1]*/nPgmTime-g_start_time<g_start_delay*1000)	//wait for start delay, number option tab 2
	//{abs_cscreen("Delay   ","","&1d       ",(g_start_delay*1000)-g_start_time);}
	wait1Msec(g_start_delay * DELAY_MULTIPLICATION_FACTOR);

	eraseDisplay();
}

#endif /* !ABS_INITIALIZE_H */
