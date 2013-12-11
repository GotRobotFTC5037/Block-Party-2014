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

void initialize()
{
	StartTask(abs_screen);
	disableDiagnosticsDisplay();
	servoChangeRate[abdd] = 3;
	servo[roger_slide] = 127;
	servo[abdd] = g_abdd_down;
	servo[grabber_left] = GRABBER_LEFT_CLOSE;
	servo[grabber_right] = GRABBER_RIGHT_CLOSE;
	memset(g_intput_array,0,6);
	selection_program();
	PlaySoundFile("! Click.rso");
	g_drift = abs_gyro_cal(g_gyro_cal_time);

	if(!HTACreadAllAxes(HTAC, g_x_axis, g_y_axis, g_z_axis)) g_error = ERR_ACCELERMOETER;
	if(g_gyro_noise>10) g_error = ERR_GYRO_CAL;
	if(HTSMUXreadPowerStatus(SENSOR_MUX)) g_error = ERR_SENSOR_MUX;
	if(HTSMUXreadPowerStatus(GYRO_MUX)) g_error = ERR_GYRO_MUX;

	if(g_error != 0)
	{
		g_screen_state = S_ERROR;
		while(true)
		{
			g_gyro_true = true;
			PlayTone (250,25);
			wait1Msec(500);
			if(nNxtButtonPressed == kEnterButton && g_error == ERR_SENSOR_MUX)break;
			if(nNxtButtonPressed == kEnterButton && g_error == ERR_ACCELERMOETER)break;
		}
	}
	LogData=true;
	g_screen_state = S_READY;
	StartTask(abs_sensors);
	StartTask(abs_datalog);
	HTANGresetAccumulatedAngle(angle_sensor);

	waitForStart();
	eraseDisplay();
	g_start_time = nPgmTime;
	g_screen_state = S_DELAY_WAIT;
	wait1Msec(g_start_delay*1000);
	eraseDisplay();
	g_screen_state = S_GYRO_SHOW;
}

#endif /* !ABS_INITIALIZE_H */
