/**
 *
 *  @file abs_reset_angle_sensor.h
 *
 *  @brief  Enter a description of what this function does
 *
 *  @param
 *
 *  @return
 *
 *  @copyright Copyright 2013, Got Robot! FTC Team 5037
 */
#ifndef ABS_RESET_ANGLE_SENSOR_H
#define ABS_RESET_ANGLE_SENSOR_H

long abs_reset_angle_sensor_val(e_angle_reset_type reset_type)
{
  if(reset_type == HARD_RESET) { HTANGresetAccumulatedAngle(angle_sensor); }

  g_angle_sensor_val = HTANGreadAccumulatedAngle(angle_sensor);

    return (g_angle_sensor_val);
}

#endif /* !ABS_RESET_ANGLE_SENSOR_H */
