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
#include <time.h>
#include "Motor.h"

#define PI 3.14
#define SENSOR_PIN 7

int pulses_per_rev = 20;
double angular_speed;
clock_t start, time_elapsed;
int prev_state = 0;

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD(get_speed) {
    int curr_state = digitalRead(SENSOR_PIN);
    printf("current state: %d \n", curr_state);
    if(curr_state != prev_state) {
        if(curr_state == 1) {
            time_elapsed = clock() - start;
            angular_speed = (2 * PI) / (pulses_per_rev * time_elapsed) / CLOCKS_PER_SEC;
            printf("Speed is: %f (rad/s)\n", angular_speed);
        }
        prev_state = curr_state;
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
    start = clock();

    int x = piThreadCreate(get_speed);
    if (x != 0) {
        printf("Thread did not start!");
    }

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
        
        // increments the duty_cycle by 5%
        if (duty_cycle <= 40)
            duty_cycle += 5;
    }


    return 0;
}
