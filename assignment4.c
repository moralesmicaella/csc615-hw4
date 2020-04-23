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
#include "Speed_Sensor.h"

#define SENSOR_PIN 8

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD (get_velocity) {
    while (1) {
        calculate_velocity();
    }
    
    return 0;
} 

/*
PI_THREAD (move_motors) {

}*/

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
    
    int speed_sensor_thread = piThreadCreate(get_velocity);
    if (speed_sensor_thread != 0) {
        printf("Failed to create a thread!");
    }

    /*
    int motor_thread = piThreadCreate(move_motors);
    if (motor_thread != 0) {
        printf("Failed to create a thread!");
    }*/

    int duty_cycle = 20;
    while (1) {
        // moves the motors forward for 5 seconds
        forward(motors, n, duty_cycle, arrows);
        delay(10000);
        
        // increments the duty_cycle by 5%
        if (duty_cycle <= 50)
            duty_cycle += 5;
    }


    return 0;
}
