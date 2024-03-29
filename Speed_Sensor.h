/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: Speed_Sensor.h
*
* Description: This is a header file that declares the variables
* and functions needed for the speed sensor to calculate speed. 
******************************************************************/

#ifndef  SPEED_SENSOR_H
#define SPEED_SENSOR_H

extern int sensor_pin;

void set_sensor_pin(int pin);
void calculate_velocity(int sampling_period);

#endif