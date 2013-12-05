/*
*
*  @file abs_S2_mission_exicute.h
*
*  @brief runs the missions from the starting point S2
*
*  @return returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_S2_MISSION_EXICUTE_H
#define ABS_S2_MISSION_EXICUTE_H

/** macros */
//=========================
// the missions for S2
//=========================
void abs_S2_mission_exicute()
{
	switch(g_mission_number)
	{
	case 0:
		g_screen_state = S_ANGLE_SHOW;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/600, 50, true);
		//abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/200, 50, true);
		//abs_turn(CLOCKWISE, POINT, TURN, 180, 60);
		//wait10Msec(300);
		//abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		//wait10Msec(300);
		//abs_turn(CLOCKWISE, POINT, TURN, 45, 60);
		//wait10Msec(300);
		//abs_turn(COUNTERCLOCKWISE, POINT, TURN, 0, 60);
		break;

	case 1:
		abs_drive(BACKWARD, E_IR_DETECT, 3, 40, true);
		PlayTone(200,20);
		//if(g_IR_angle_dist_complete == true) g_end_point = 12;
		if(g_end_point == 2)
		{
			if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(62*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate4_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(100*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate3_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(137*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate2_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(162*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate1_to_turn_dist;
		}
		else if(g_end_point == 3)
		{
			if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(62*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate4_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(100*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate3_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(137*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate2_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(162*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate1_to_turn_dist;
		}
		wait1Msec(1000);
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/6, 50, true);
		wait1Msec(500);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 2:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate4_to_turn_dist;
		else g_to_turn_dist = g_forward_crate4_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/40, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 3:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate3_to_turn_dist;
		else g_to_turn_dist = g_forward_crate3_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/65, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 4:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate2_to_turn_dist;
		else g_to_turn_dist = g_forward_crate2_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/115, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 5:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate1_to_turn_dist;
		else g_to_turn_dist = g_forward_crate1_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/140, 50, true);
		wait1Msec(2000);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 6:
		abs_turn(CLOCKWISE, POINT, TURN, 75, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 190, 50, true);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 75, 60);
		abs_drive(FORWARD, E_ANGLE, 80, 50, true);
		break;

	case 7:
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 98, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 87, 50, true);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		abs_turn(CLOCKWISE, POINT, TURN, 103, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		abs_drive(FORWARD, E_ANGLE, 80, 50, true);
		break;

	case 140:
		int dist = 30;
		bool done = false;
		while(done == false)
		{
			int ac_start_time = nPgmTime;
			int i = 0;
			while((g_accelermoeter_sensor < dist+5) && (g_accelermoeter_sensor > dist-5) && ((ac_start_time - nPgmTime)<500))
			{
				i++;
				PlayTone(20,20);
				wait1Msec(1);
			}
			if(i > 490) done = true;
			PlayTone(20,20);
		}
		break;
	}
	wait1Msec(g_end_delay*1000);
	switch(g_end_point)
	{
	case 1:
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		motor[right_motor] = 0;
		motor[left_motor] = 0;
		motor[sky_hook] = 0;
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		break;
	case 2:
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		abs_drive(FORWARD, E_ANGLE, g_to_turn_dist, 50, true);
		wait1Msec(200);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 75, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 85, 50, true);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT) abs_turn(CLOCKWISE, POINT, TURN, 90, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		if(auto_grabber_selection_ramp_options == SUB_SELECTION_RAMP_STOP)
		{
			if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_drive(FORWARD, E_ANGLE, 80, 50, true);
			else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT) abs_drive(BACKWARD, E_ANGLE, 80, 50, true);
		}
		else abs_drive(FORWARD, E_ANGLE, 130, 50, true);
		break;
	case 3:
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		abs_drive(BACKWARD, E_ANGLE, g_to_turn_dist, 50, true);
		wait1Msec(200);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 87, 50, true);
		wait1Msec(500);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_turn(CLOCKWISE, POINT, TURN, 84, 50);
		else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT)abs_turn(COUNTERCLOCKWISE, POINT, TURN, 85, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		if(auto_grabber_selection_ramp_options == SUB_SELECTION_RAMP_STOP)
		{
			if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_drive(FORWARD, E_ANGLE, 80, 50, true);
			else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT)abs_drive(BACKWARD, E_ANGLE, 80, 50, true);
		}
		else abs_drive(FORWARD, E_ANGLE, 130, 50, true);
		break;
	case 12:
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		abs_drive(FORWARD, E_ANGLE, g_forward_crate4_to_turn_dist, 50, true);
		wait1Msec(200);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 75, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 85, 50, true);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_turn(COUNTERCLOCKWISE, POINT, TURN, 90, 60);
		else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT) abs_turn(CLOCKWISE, POINT, TURN, 90, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		if(auto_grabber_selections == SUB_SELECTION_GRABBERS_IN) abs_drive(FORWARD, E_ANGLE, 80, 50, true);
		else if(auto_grabber_selections == SUB_SELECTION_GRABBERS_OUT) abs_drive(BACKWARD, E_ANGLE, 80, 50, true);
		break;
	}
}

#endif /* !ABS_S2_MISSION_EXICUTE_H */
