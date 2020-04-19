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

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD(get_speed) {

    return 0;
}

int main(void) {
    int duty_cycle = 10;
    int num_of_pulses, time;
    double angular_speed;
    int pulses_per_rev = 20;

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

    if (setup(motors, n, arrows) == -1) 
        return -1;
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
        
        // increments the duty_cycle by 10%
        if (duty_cycle <=90)
            duty_cycle += 10;
    }


    return 0;
}
