#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define PI 3.14
#define SENSOR_PIN 7

int pulses_per_rev = 20;
double angular_speed;
int start, time_elapsed;
int sampling_period = 1000;
int pulses = 0;

void getSpeed() {
    start = millis();
    while(1) {
        time_elapsed = millis() - start;
        while(time_elapsed < sampling_period) {
            if (digitalRead(SENSOR_PIN) == 1) {
                pulses++;
            } 
            time_elapsed = millis() - start;
        }
        printf("Number of pulses: %d \n", pulses);
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