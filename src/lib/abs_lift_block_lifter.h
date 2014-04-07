/**
 *
 *  @file abs_lift_block_lifter.h
 *
 *  @brief  Enter a description of what this function does
 *
 *  @param None N/A
 *
 *  @return Returns nothing
 *
 *  @copyright Copyright 2013, Got Robot! FTC Team 5037
 */
#ifndef ABS_LIFT_BLOCK_LIFTER_H
#define ABS_LIFT_BLOCK_LIFTER_H

#include "global_variables.h"

task abs_lift_block_lifter()
{
	motor[block_lift_motor] = g_end_ramp_lift_speed;
	motor[block_lift_motor2] = g_end_ramp_lift_speed;
	wait1Msec(750);
	motor[block_lift_motor] = 0;
	motor[block_lift_motor2] = 0;
}

#endif /* !TEMPLATE_H */
