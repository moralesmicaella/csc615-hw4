#include <stdio.h>
#include <wiringPi.h>
#include "Speed_Sensor.h"

#define PI 3.14

const int pulses_per_rev = 20;
const int radius =  1.25;

double linear_velocity;
int start = millis(), time_elapsed;
int pulses=0, sampling_period = 1000;

void calculate_velocity() {
    time_elapsed = millis() - start;
    while(time_elapsed < sampling_period) {
        if (digitalRead(SENSOR_PIN)) {
            pulses++;
            while(digitalRead(SENSOR_PIN));
        } 
        time_elapsed = millis() - start;
    }
    time_elapsed /= 1000;
    linear_velocity = (2 * PI * radius * pulses) / (pulses_per_rev * time_elapsed);
    printf("Speed is: %f (cm/s)\n", linear_velocity);
    pulses =  0;
    start = millis();
    
}