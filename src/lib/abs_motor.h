/**
 *
 *  @file abs_motor.h
 *
 *  @brief  Allows the robot to move attachments in auto.c
 *
 *  @param move_type lets the robot know what attchment to move
 *
 *  @param power tells the robot how much power it should use on the attachment
 *
 *  @return Returns nothing
 *
 *  @copyright Copyright 2013, Got Robot! FTC Team 5037
 */
#ifndef ABS_MOTOR_H
#define ABS_MOTOR_H

void abs_motor(e_motor_move move_type)
{
	dl_step = dl_step+1;
	//-----------------------------
	// roger slide
	//-----------------------------
	if(move_type == ROGER_SLIDE) servo[roger_slide] = 0;

	//-----------------------------
	// ABDD
	//-----------------------------
	if(move_type == ABDD)
	{
		servo[abdd] = g_abdd_up;
		wait10Msec(70);
		servo[abdd] = g_abdd_down;
	}
}

#endif /* !ABS_MOTOR_H */
