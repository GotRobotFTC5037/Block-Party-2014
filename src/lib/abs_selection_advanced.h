/**
*
*  @file abs_selection_advanced.h
*
*  @brief handles the custom selection options for auto mission selection
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SELECTION_ADVANCED_H
#define ABS_SELECTION_ADVANCED_H

#include "lib/abs_ramp_interpret.h"

void abs_selection_advanced()
{
	//---------------------------------------
	// Start of cornor time selection
	//---------------------------------------
	g_input_array[CORNOR_DELAY] = 0;

	while(nNxtButtonPressed != kEnterButton)
	{
		abs_cscreen("Corner  ","delay   ","%2d",g_input_array[CORNOR_DELAY]);
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_input_array[CORNOR_DELAY] < 30) g_input_array[CORNOR_DELAY]++;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_input_array[CORNOR_DELAY] > 0) g_input_array[CORNOR_DELAY]--;
		}
	}

	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}

	//---------------------------------------
	// Start of ramp delay selection
	//---------------------------------------
	g_input_array[RAMP_DELAY] = 0;

	while(nNxtButtonPressed != kEnterButton)
	{
		abs_cscreen("Ramp    ","delay   ","%2d",g_input_array[RAMP_DELAY]);
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_input_array[RAMP_DELAY]< 30) g_input_array[RAMP_DELAY]++;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_input_array[RAMP_DELAY] > 0) g_input_array[RAMP_DELAY]--;
		}
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}

	abs_ramp_interpret();
}

#endif /* !ABS_SELECTION_ADVANCED_H */
