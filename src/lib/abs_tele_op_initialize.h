/**
 *
 *  @file template.h (this should be the name of the function)
 *
 *  @brief  Enter a description of what this function does
 *
 *  @param
 *
 *  @return
 *
 *  @copyright Copyright 2013, Got Robot! FTC Team 5037
 */
#ifndef ABS_TELE_OP_INITIALIZE_H
#define ABS_TELE_OP_INITIALIZE_H

void abs_tele_op_initialize()
{
if(joystick.joy1_TopHat == -1) Joy1Enabled = true;
if(joystick.joy2_TopHat == -1) Joy2Enabled = true;

StartTask(screen);
screen_state = s_ready;
}
#endif /* !TEMPLATE_H */
