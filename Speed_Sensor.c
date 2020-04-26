/******************************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: Speed_Sensor.c
*
* Description: This a file that defines the variables and functions in 
* Speed_Sensor.h
*
* Reference:
* https://www.electronicshub.org/interfacing-lm393-speed-sensor-with-arduino/
******************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include "Speed_Sensor.h"

#define PI 3.14

const int sensor_pin;
const int pulses_per_rev = 20;
const int radius =  1.25;
const int sampling_period = 1000;

double linear_velocity;
int start, time_elapsed;
int pulses;

// sets the sensor pin to input mode
void set_sensor_pin(int pin) {
    sensor_pin = pin;
    pinMode(pin, INPUT);
}

void reset_calculation() {
    pulses = 0;
    time_elapsed = 0;
    linear_velocity = 0;
}

// calculates the velocity using the pulse counting method
void calculate_velocity() {
    pulses =  0;
    start = millis();
    time_elapsed = millis() - start;
    while(time_elapsed < sampling_period) {
        if (digitalRead(sensor_pin)) {
            pulses++;
            while(digitalRead(sensor_pin));
        } 
        time_elapsed = millis() - start;
    }
    time_elapsed /= 1000;
    linear_velocity = (2 * PI * radius * pulses) / (pulses_per_rev * time_elapsed);
    printf("Speed is: %f (cm/s)\n", linear_velocity);
}