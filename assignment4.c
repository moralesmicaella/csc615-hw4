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

int main(void) {
    Motor motors[] = {m1, m2};
    int n = sizeof(motors) / sizeof(motors[0]);

    // wiringPi 25 = P37, wiringPi 23 = P33
    Arrow arrows = {.af = 25, .ab = 23};

    int speed = 10;
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (setup(motors, n, arrows) == -1) 
        return -1;
    while (1) {
        // moves the motors forward for 5 seconds
        forward(motors, n, speed, arrows);
        delay(5000);
        
        // stops the motor for 2 seconds
        stop(motors, n, arrows);
        delay(2000);

        // moves the motors backward for 5 seconds
        backward(motors, n, speed, arrows);
        delay(5000);

        // stops the motor for 2 seconds
        stop(motors, n, arrows);
        delay(2000);
        
        // increments the speed by 10%
        if (speed <=90)
            speed += 10;
    }


    return 0;
}
