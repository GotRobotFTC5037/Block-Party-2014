/**
*
*  @file abs_smoke_test_view.h
*
*  @brief A header file that shows the view for smoketest
*
*  @param
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_SMOKE_TEST_VIEW_H
#define ABS_SMOKE_TEST_VIEW_H

#include "abs_cscreen.h"

void abs_smoke_test_view(int test_num,int test_value1, int test_value2)
{
	switch(test_num)
	{
	case 1: abs_cscreen("Block   ","lift    ","%1d       ",test_value1); break;
	case 2: abs_cscreen("Sky Hook","        ","%1d       ",test_value1); break;
	case 3: abs_cscreen("Drive   ","        ","%1d       ",test_value1); break;
	case 4: abs_cscreen("Grabbers","L   R   ","%1d %1d     ",test_value1,test_value2); break;
	case 5: abs_cscreen("ABDD    ","        ","%1d       ",test_value1); break;
	case 6: abs_cscreen("Pillow  ","slide   ","%1d       ",test_value1); break;
	case 7: abs_cscreen("Pillow  ","spinner ","%1d       ",test_value1); break;
	case 8: abs_cscreen("EOPD    ","servo   ","%1d       ",test_value1); break;
	case 9: abs_cscreen("angle   ","ASU  BPU","%1d %4d     ",test_value1,test_value2); break;
	default: abs_cscreen("ERROR   ","        ","        "); break;
	}
}

#endif /* !ABS_SMOKE_TEST_VIEW_H */
