#include <stdio.h>
#include <wiringPi.h>
#include "Speed_Sensor.h"

#define PI 3.14

int sensor_pin;
const int pulses_per_rev = 20;
const int radius =  1.25;

double linear_velocity;
int start, time_elapsed;
int pulses=0, sampling_period = 1000;

void set_sensor_pin(int pin) {
    sensor_pin = pin;
}

void calculate_velocity() {
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
    pulses =  0;
}