/**
*
*  @file abs_turn.h
*
*  @brief The header file that alows you to do a point turn
*
*  @param degree Tells the robot how much to turn
*
*  @param dir Tells the robot what way to turn
*
*  @param speed Tells the robot how fast to turn
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SET_HEADING_H
#define ABS_SET_HEADING_H

#include "abs_dlog.h"

/** macros */
typedef enum
{
	RELATIVE,
	CONSTANT,
	RELATIVE_CONSTANT
} e_heading_reset_type;

#define abs_reset_heading(X) abs_set_heading(X, ALL_GYROS, 0.0)

bool g_heading_lock = false;

//=======================================
// turn
//=======================================
int abs_set_heading(e_heading_reset_type type, e_gyro_names gyro_to_set, float value)
{
  while(g_heading_lock) { wait1Msec(10); }

  g_heading_lock = true;

  switch(type)
  {
  	case RELATIVE:
  	  if(gyro_to_set == GYRO1 || gyro_to_set == ALL_GYROS)	g_rel_heading1 = value;
 			if(gyro_to_set == GYRO2 || gyro_to_set == ALL_GYROS) g_rel_heading2 = value;
 			if(gyro_to_set == SELECTED_GYRO) g_rel_heading_use = value;
 			return 1;
 			break;

  	case CONSTANT:
  		if(gyro_to_set == GYRO1 || gyro_to_set == ALL_GYROS) g_const_heading1 = value;
 			if(gyro_to_set == GYRO2 || gyro_to_set == ALL_GYROS) g_const_heading2 = value;
 			if(gyro_to_set == SELECTED_GYRO) g_const_heading_use = value;
 			return 1;
 			break;

  	case RELATIVE_CONSTANT:
  	  if(gyro_to_set == GYRO1 || gyro_to_set == ALL_GYROS)
  	  {
  	  	g_rel_heading1 = value;
  	  	g_const_heading1 = value;
 		  }
  	  if(gyro_to_set == GYRO2 || gyro_to_set == ALL_GYROS)
  	  {
  	  	g_rel_heading2 = value;
  			g_const_heading2 = value;
  		}
  		if(gyro_to_set == SELECTED_GYRO)
  	  {
  	  	g_rel_heading_use = value;
  			g_const_heading_use = value;
  		}
 			return 1;
 			break;

  	default:
  		/** log a meaningful error here */
  		return 0;
  		break;
  	}

    g_heading_lock = false;

}

#endif /* !ABS_TURN_H */
