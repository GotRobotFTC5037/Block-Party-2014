/**
*
*  @file abs_ramp_interpret.h
*
*  @brief
*
*  @param None N/A
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_RAMP_INTERPRET_H
#define ABS_RAMP_INTERPRET_H

/** macros */
void abs_ramp_interpret()
{
	g_start_point = g_input_array[STARTING_POINT];
	g_start_delay = g_input_array[STARTING_DELAY];
	g_mission_number = g_input_array[SCOREING_POINT];
	g_end_delay = g_input_array[END_DELAY];
	if(g_input_array[END_POINT] <= 3 && g_input_array[END_POINT] >= 1)
	{
		g_end_point = g_input_array[END_POINT];
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_STOP;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_ALLY_SIDE;
	}
	else if(g_input_array[END_POINT]==6||g_input_array[END_POINT]==7)
	{
		if(g_input_array[END_POINT]==6)g_end_point = 2;
		else g_end_point = 3;
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_STOP;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_OPP_SIDE;
	}
	else if(g_input_array[END_POINT] == 4)
	{
		g_end_point = 2;
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_CONTINUED;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_ALLY_SIDE;
	}
	else if(g_input_array[END_POINT] == 5)
	{
		g_end_point = 3;
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_CONTINUED;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_ALLY_SIDE;
	}
	else if(g_input_array[END_POINT] == 8)
	{
		g_end_point = 2;
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_CONTINUED;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_OPP_SIDE;
  }
	else if(g_input_array[END_POINT] == 9)
	{
		g_end_point = 3;
		g_auto_selection_ramp_continue_options = SUB_SELECTION_RAMP_CONTINUED;
		g_auto_sub_selection_ramp_side = SUB_SELECTION_RAMP_OPP_SIDE;
  }
	else g_end_point = 1; //error for if an invaid value is inputed
	if(g_start_point==3||g_start_point==4)
	{
		g_em_first_turn_type = RELATIVE_TURN;
		g_em_second_turn_type = RELATIVE_TURN;
	}
}
#endif /* !ABS_RAMP_INTERPRET_H */
