/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: assignment4.c
*
* Description: This program 
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

PI_THREAD(get_velocity) {
    while (1) {
        calculate_velocity();
    }
    return 0;
} 

int main(void) {
    Motor motors[] = {m1, m2};
    int n = sizeof(motors) / sizeof(motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(motors, n, arrows);
    set_sensor_pin(SENSOR_PIN);
    
    // creates the thread to read input from the speed sensor 
    // and calculate the velocity of the wheel encoder
    int speed_sensor_thread = piThreadCreate(get_velocity);
    if (speed_sensor_thread != 0) {
        printf("Failed to create a thread!");
    }

    int duty_cycle = 20;
    for(int i = 1; i < 5; i++) {
        // moves the motors forward for 4 seconds
        forward(motors, n, duty_cycle, arrows);
        delay(4000);
        
        // increments the duty_cycle by 10%
        duty_cycle += 10;
    }

    // stops the motor
    stop(motors, n, arrows);

    return 0;
}
