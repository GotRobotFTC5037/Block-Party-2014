/**
 *
 *  @file abs_tele_op_initialize.h
 *
 *  @brief  does some important stuff before we do the teleop program
 *
 *  @param None n/a
 *
 *  @return Returns nothing
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 */
#ifndef ABS_TELE_OP_INITIALIZE_H
#define ABS_TELE_OP_INITIALIZE_H


void abs_tele_op_initialize()
{
	if(joystick.joy1_TopHat == -1) g_joy1_enabled = true;
	if(joystick.joy2_TopHat == -1) g_joy2_enabled = true;

	servoChangeRate[abdd] = 10;
	servo[abdd] = g_abdd_down;

	getJoystickSettings(joystick);
}
#endif /* ABS_TELE_OP_INITIALIZE_H */
