/**
*
*  @file abs_selection_options.h
*
*  @brief
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SELECTION_OPTIONS_H
#define ABS_SELECTION_OPTIONS_H

#include "lib/abs_cscreen.h"

void abs_selection_options()
{
	//---------------------------------------
	// first turn
	//---------------------------------------
	g_selection_turn = 1;

	while(nNxtButtonPressed == kEnterButton){}
	while(nNxtButtonPressed != kEnterButton)
	{
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_em_first_turn_type == RELATIVE_TURN)  g_em_first_turn_type = CONSTANT_TURN;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_em_first_turn_type == CONSTANT_TURN) g_em_first_turn_type = RELATIVE_TURN;
		}
		if(g_em_first_turn_type == RELATIVE_TURN) abs_cscreen("Options ","1st turn","rel     ");
		else abs_cscreen("Options ","1st turn","const   ");
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
	eraseDisplay();

	//---------------------------------------
	// second turn selection
	//---------------------------------------

	g_selection_turn = 2;

	while(nNxtButtonPressed != kEnterButton)
	{
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_em_second_turn_type == RELATIVE_TURN) g_em_second_turn_type = CONSTANT_TURN;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_em_second_turn_type == CONSTANT_TURN) g_em_second_turn_type = RELATIVE_TURN;
		}
		if(g_em_second_turn_type == RELATIVE_TURN) abs_cscreen("Options ","2st turn","rel     ");
		else abs_cscreen("Options ","2st turn","const   ");
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
	eraseDisplay();
	//---------------------------------------
	// stand ground
	//---------------------------------------
	while(nNxtButtonPressed != kEnterButton)
	{
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_stay_on_ramp == true) g_stay_on_ramp = false;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_stay_on_ramp == false) g_stay_on_ramp = true;
		}
		if(g_stay_on_ramp == true) abs_cscreen("Stay on ","ramp    ","true    ");
		else abs_cscreen("Stay on ","ramp    ","false   ");
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
	//---------------------------------------
	// IR partial selection
	//---------------------------------------
	static int j = 1;
	while(nNxtButtonPressed != kEnterButton)
	{
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(j<3) j++;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(j>1) j--;
		}
		if(j==1)
		{
			g_auto_sub_selection_IR_partial = SUB_SELECTION_IR_ALL;
			abs_cscreen("IR      ","partial ","ALL     ");
		}
		else if(j==2)
		{
			g_auto_sub_selection_IR_partial = SUB_SELECTION_IR_1_2;
			abs_cscreen("IR      ","partial ","1 & 2   ");
		}
		else
		{
			g_auto_sub_selection_IR_partial = SUB_SELECTION_IR_3_4;
			abs_cscreen("IR      ","partial ","3 & 4   ");
		}
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
}

#endif /* !ABS_SELECTION_OPTIONS_H */
