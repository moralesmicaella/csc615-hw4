/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: assignment4.c
*
* Description:
* 
******************************************************************/

#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"

#define PI 3.14
#define SENSOR_PIN 7

int pulses_per_rev = 20;
double angular_speed;
int start, time_elapsed;
int sampling_period = 1000;
int pulses = 0;

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

void* get_speed(void* arg) {
    start = millis();
    while(1) {
        time_elapsed = millis() - start;
        while(time_elapsed < sampling_period) {
            if (digitalRead(SENSOR_PIN) == 1) {
                pulses++;
                printf("Number of pulses: %d \n", pulses);
                while(digitalRead(SENSOR_PIN) == 1);
            } 
            time_elapsed = millis() - start;
        }
        angular_speed = (2 * PI * pulses) / (pulses_per_rev);
        printf("Speed is: %f (rad/s)\n", angular_speed);
        pulses =  0;
        start = millis();
    }
    
    return 0;
}

int main(void) {
    Motor motors[] = {m1, m2};
    int n = sizeof(motors) / sizeof(motors[0]);

    // wiringPi 25 = P37, wiringPi 23 = P33
    Arrow arrows = {.af = 25, .ab = 23};
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(motors, n, arrows);
    
    pinMode(SENSOR_PIN, INPUT);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &get_speed, NULL);
    /*int thread = piThreadCreate(get_speed);
    if (thread != 0) {
        printf("Failed to create a thread!");
    }*/

    int duty_cycle = 10;
    while (1) {
        // moves the motors forward for 5 seconds
        forward(motors, n, duty_cycle, arrows);
        delay(5000);
        
        // stops the motor for 2 seconds
        stop(motors, n, arrows);
        delay(2000);

        // moves the motors backward for 5 seconds
        backward(motors, n, duty_cycle, arrows);
        delay(5000);

        // stops the motor for 2 seconds
        stop(motors, n, arrows);
        delay(2000);
        
        // increments the duty_cycle by 2%
        if (duty_cycle <= 30)
            duty_cycle += 2;
    }


    return 0;
}
