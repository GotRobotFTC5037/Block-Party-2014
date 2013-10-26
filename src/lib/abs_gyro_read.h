/**
*
*  @file abs_gyro_read.h
*
*  @brief A hedder file that allows you to read the input comming from the gyro
*
*	 @param gyro Gyro raw sensor value
*
*  @param tcontext Pointer to turn context
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_GYRO_READ_H
#define ABS_GYRO_READ_H

void abs_gyro_read (int GYRO, move_context* tcontext)
{
	float currtime;
	float rawgyro = 0;
	currtime=nPgmTime;
	rawgyro = HTGYROreadRot(GYRO);

	tcontext->heading += (rawgyro - g_drift) * (float)(currtime - tcontext->time)/1000;

			nxtDisplayCenteredBigTextLine(3, "%2.0f", rawgyro);
			nxtDisplayCenteredBigTextLine(5, "%2.0f", tcontext->heading);

	//relHeading += (rawgyro - drift) * (float)(currtime - tcontext->time)/1000;
	tcontext->time = currtime;
}

#endif /* !ABS_GYRO_READ_H */
