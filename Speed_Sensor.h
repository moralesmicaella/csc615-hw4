#ifndef  SPEED_SENSOR_H
#define SPEED_SENSOR_H

extern int sensor_pin;

void set_sensor_pin(int pin);
void calculate_velocity();

#endif