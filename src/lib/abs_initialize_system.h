/**
*
*  @file abs_initialize_system()
*
*  @brief Calibrates all sensors and prepares memory for use
*
*  @copyright Copyright 2013, Got Robot! FTC Team 5037
*/
#ifndef ABS_INITIALIZE_SYSTEM_H
#define ABS_INITIALIZE_SYSTEM_H

/** macros */
void abs_initialize_system()
{
	abs_create_mem();
	g_drift = abs_gyro_cal(CALIBRATION_TIME);

	//====================================================
	// Drift file write for tele-op
	//====================================================
	string sFileName = TELE_OP_PARAMITER_FILE_NAME;
	TFileIOResult nIoResult;
	TFileHandle hFileHandle;
	int nFileSize = TELE_OP_PARAMITER_FILE_SIZE;

	Delete(sFileName, nIoResult);
	OpenWrite ( hFileHandle, nIoResult, sFileName, nFileSize);
	if(nIoResult != 0)
	{
		abs_report_error(TEXT_FILE, DONT_EXIT);
	}
	else
	{
		WriteFloat( hFileHandle, nIoResult, g_drift);
		if(nIoResult != 0)
		{
			abs_report_error(TEXT_FILE, DONT_EXIT);
		}
		else
		{
			//WriteFloat( hFileHandle, nIoResult, Driver_Cal);
			Close(hFileHandle, nIoResult);
		}
	}
}
	/** enumerations */

	/** structures */

	/** function prototypes */

	/** global constant variables */

#endif /* !ABS_INITIALIZE_SYSTEM_H */
