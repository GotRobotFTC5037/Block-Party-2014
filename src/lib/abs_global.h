/**
 *
 *  @file abs_global.h
 *
 *  @brief  Enter a description of what this file contains
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */
#ifndef ABS_GLOBAL_H
#define ABS_GLOBAL_H

/** macros */
/** defines memory size */
#define DYNAMIC_MEMORY_SIZE 40
#define CALIBRATION_TIME 4000
#define ANGLE_SENSOR_CIRCUMFERENCE 26
char* g_next_available_memory_ptr;
char g_buffer[DYNAMIC_MEMORY_SIZE];
float g_drift;
typedef enum
{
	NULL_POINTER
} e_exit_code;
#endif /* !ABS_H */
