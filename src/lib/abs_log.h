/**
*
*  @file abs_log.h
*
*  @brief A function that handels the data log
*
*  @param None N/A
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_LOG_H
#define ABS_LOG_H

/** macros */
void abs_log(const char * input1,const char * input2, int input3, int input4, int input5,int input6)
{

	StringFormat(sString, "");
	strcat(sString,CRLF);
	WriteText(LogFileHandle, LogIoResult, sString);

	StringFormat(sString, "%4d\t",nPgmTime);
	WriteText(LogFileHandle, LogIoResult, sString);

	if(!strcmp(input1,""))StringFormat(sString, input1);
	else StringFormat(sString, "");
	WriteText(LogFileHandle, LogIoResult, input1);

	StringFormat(sString, "\t");
	WriteText(LogFileHandle, LogIoResult, sString);

	if(!strcmp(input1,""))StringFormat(sString, input2);
	else StringFormat(sString, "");
	WriteText(LogFileHandle, LogIoResult, input2);

	StringFormat(sString, "\t");
	WriteText(LogFileHandle, LogIoResult, sString);

	StringFormat(sString, "%4d\t", input3);
	WriteText(LogFileHandle, LogIoResult, sString);

	StringFormat(sString, "%4d\t", input4);
	WriteText(LogFileHandle, LogIoResult, sString);

	StringFormat(sString, "%4d\t", input5);
	WriteText(LogFileHandle, LogIoResult, sString);

	StringFormat(sString, "%4d\t", input6);
	WriteText(LogFileHandle, LogIoResult, sString);

	if(input1=="abs_drive.h")
	{
		StringFormat(sString, "rel-g %4d\t", g_rel_heading);
		WriteText(LogFileHandle, LogIoResult, sString);

		StringFormat(sString, "cnst-g %4d\t", g_const_heading);
		WriteText(LogFileHandle, LogIoResult, sString);
	}
}
#endif /* !ABS_LOG_H */
