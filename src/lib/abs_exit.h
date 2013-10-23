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

/** macros */
void abs_exit(e_exit_code exit)
{
	if (exit == NULL_POINTER)
	{
		eraseDisplay();
		nxtDisplayString(2,"ERROR!!!");
		nxtDisplayString(3,"ERROR CODE: 1");
		nxtDisplayString(4,"NOT ENOUGH MEMORY!!!");
		nxtDisplayString(5,"ADD MORE MEMORY OR ADD A");
		nxtDisplayString(5,"WAY TO FREE MEMORY");
		PlayTone(4000, 50);
		wait10Msec(500);
		StopAllTasks();
	}
}
//Error code 1: Not enough memory
/** enumerations */

/** structures */

/** function prototypes */

/** global constant variables */

#endif /* !TEMPLATE_H */
