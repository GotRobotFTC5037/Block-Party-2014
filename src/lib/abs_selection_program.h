/**
*
*  @file abs_selection_program.h
*
*  @brief A header file that handles the begining selection for robot actions
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SELECTION_PROGRAM_H
#define ABS_SELECTION_PROGRAM_H

#include "abs_selection_custom.h"
#include "abs_selection_number.h"
#include "abs_selection_quick.h"
#include "abs_selection_advanced.h"
#include "abs_selection_options.h"
#include "lib/abs_cscreen.h"

void abs_selection_program()
{
	while(nNxtButtonPressed == kEnterButton){}

	//---------------------------------------
	// number selection, quick selection, or custom selection
	//---------------------------------------
	int j = 1;
	while(nNxtButtonPressed != kEnterButton)
	{
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(j < 5) j++;
			else j = 5;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(j > 1) j--;
			else j = 1;
		}
		switch(j)
		{
		case 1: abs_cscreen("Selectin","type    ","CUSTOM  ");
		selection_type = SELECTION_TYPE_CUSTOM; break;
		case 2: abs_cscreen("Selectin","type    ","NUMBER  ");
		selection_type = SELECTION_TYPE_NUMBER; break;
		case 3: abs_cscreen("Selectin","type    ","QUICK   ");
		selection_type = SELECTION_TYPE_QUICK; break;
		case 4: abs_cscreen("Selectin","type    ","ADVANCED");
		selection_type = SELECTION_TYPE_ADVANCED; break;
		case 5: abs_cscreen("Selectin","type    ","OPTION  ");
		selection_type = SELECTION_TYPE_OPTIONS; break;
		}
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
	eraseDisplay();

	//---------------------------------------
	// selection executes
	//---------------------------------------
	if(selection_type == SELECTION_TYPE_CUSTOM) abs_selection_custom();
	if(selection_type == SELECTION_TYPE_NUMBER)abs_selection_number();
	if(selection_type == SELECTION_TYPE_QUICK) abs_selection_quick();
	if(selection_type == SELECTION_TYPE_ADVANCED)
	{
		abs_selection_custom();
		abs_selection_advanced();
	}
	if(selection_type == SELECTION_TYPE_OPTIONS)
	{
		abs_selection_options();
		abs_selection_program();
	}
	//---------------------------------------
	// Start of gyro cal selection
	//---------------------------------------

	while(nNxtButtonPressed != kEnterButton)
	{
		abs_cscreen("GyroCal ","time    ","%1d       ",g_gyro_cal_time);
		if(nNxtButtonPressed == kRightButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kRightButton){}
			if(g_gyro_cal_time < 30) g_gyro_cal_time++;
		}
		if(nNxtButtonPressed == kLeftButton)
		{
			PlaySoundFile("! Click.rso");
			while(nNxtButtonPressed == kLeftButton){}
			if(g_gyro_cal_time > 0) g_gyro_cal_time--;
		}
	}
	PlaySoundFile("! Click.rso");
	while(nNxtButtonPressed == kEnterButton){}
	eraseDisplay();
	for(int i=1;i<6;i++)abs_dlog(__FILE__ ,"","",g_input_array[i]);
}

#endif /* !ABS_SELECTION_PROGRAM_H */
