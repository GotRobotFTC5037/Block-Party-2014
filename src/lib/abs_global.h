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
#define DYNAMIC_MEMORY_SIZE 80
#define CALIBRATION_TIME 4000
#define ANGLE_SENSOR_CIRCUMFERENCE 26
#define JOYSTICK_METHOD NON_LINEAR
#define TELE_OP_PARAMITER_FILE_SIZE 100
#define TELE_OP_PARAMITER_FILE_NAME "tele_op_paramiter_pass.txt"
char* g_next_available_memory_ptr;
char g_buffer[DYNAMIC_MEMORY_SIZE];
float g_drift;
typedef enum
{
	NULL_POINTER,
	TEXT_FILE
} e_exit_code;
#endif /* !ABS_H */
