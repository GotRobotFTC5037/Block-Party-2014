/**
*
*  @file abs_exit.h
*
*  @brief  Exits the program in case something goes wrong or if we just want to gracefully exit the program
*
*  @param exit tells the program what the exit name is
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_EXIT_H
#define ABS_EXIT_H
//--------------------------
//Reports a error in the program abd quits if i can cause damage to the robot
//--------------------------
/** macros */
void abs_report_error(e_exit_code exit, e_exit e_stop)
{
	if (exit == NULL_POINTER)//if there us a null pointer error
	{
		eraseDisplay();
		nxtDisplayString(2,"FATAL ERROR!!!");
		nxtDisplayString(3,"ERROR CODE: 1");
		nxtDisplayString(4,"NOT ENOUGH MEMORY!!!");
		PlayTone(10000, 50);
		wait10Msec(500);
		if(e_stop == EXIT)
		StopAllTasks();
	}
	else if(exit == TEXT_FILE)//if there is a text file error
	{
		eraseDisplay();
		nxtDisplayString(2,"ERROR!!!");
		nxtDisplayString(3,"ERROR CODE: 2");
		nxtDisplayString(4,"PROBLEM WITH TEXT FILE");
		PlayTone(2000, 50);
		wait10Msec(500);
		if(e_stop == EXIT)
		StopAllTasks();
	}
}
//Error code 1: Not enough memory
/** enumerations */

/** structures */

/** function prototypes */

/** global constant variables */

#endif /* !TEMPLATE_H */
