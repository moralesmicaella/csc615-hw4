/******************************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: Speed_Sensor.c
*
* Description: This is a c file that defines the variables and functions in 
* Speed_Sensor.h
*
* Reference:
* https://www.electronicshub.org/interfacing-lm393-speed-sensor-with-arduino/
******************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include "Speed_Sensor.h"

#define PI 3.14

int sensor_pin;
const int pulses_per_rev = 20;
const int radius =  1.25;

double linear_velocity;
int start, end, pulses;
int count, prev_count=0;

// sets the sensor pin to input mode
void set_sensor_pin(int pin) {
    sensor_pin = pin;
    pinMode(pin, INPUT);
}

/*
* counts the number of pulses over the given sampling period and
* uses it to calculate the velocity of an optical wheel encoder
* it prints the velocity in cm/s
*/
void calculate_velocity(int sampling_period) {
    start = millis();
    end = start + sampling_period;
    while(start < end) {
        if (digitalRead(sensor_pin)) {
            count++;
            while(digitalRead(sensor_pin));
        } 
        start = millis();
    }
    pulses = count - prev_count;
    prev_count = count;
    sampling_period /= 1000; // convert to seconds
    linear_velocity = (2 * PI * radius * pulses) / (pulses_per_rev * sampling_period);
    printf("Speed is: %f (cm/s)\n", linear_velocity);
}