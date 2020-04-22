#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define PI 3.14
#define SENSOR_PIN 0

int pulses_per_rev = 20;
double angular_speed;
int start, time_elapsed, signal;
int sampling_period = 1000;
int pulses = 0;

void getSpeed() {
    start = millis();
    while(1) {
        time_elapsed = millis() - start;
        while(time_elapsed < sampling_period) {
            signal = digitalRead(SENSOR_PIN);
            //printf("signal: %d \n", signal);
            if (signal == 1) {
                pulses++;
                printf("Number of pulses: %d \n", pulses);
                signal = digitalRead(SENSOR_PIN);
                while(signal == 1);
            } 
            time_elapsed = millis() - start;
        }
        angular_speed = (2 * PI * pulses) / (pulses_per_rev);
        printf("Speed is: %f (rad/s)\n", angular_speed);
        pulses =  0;
        start = millis();
    }
    
}

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 
    pinMode(SENSOR_PIN, INPUT);
    getSpeed();

    return 0;
}