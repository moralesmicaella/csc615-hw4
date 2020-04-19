/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & duty_cycle Encoder
* File: Motor.c
*
* Description:
* 
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"

int keyboard_interrupt = 0;

// wiringPi 0 = P11, wiringPi 2 = P13, wiringPi 3 = P15
Motor m1 = {.num = 1, .e = 0, .f = 2, .r = 3};
// wiringPi 6 = P22, wiringPi 4 = P16, wiringPi 5 = P18
Motor m2 = {.num = 2, .e = 6, .f = 4, .r = 5}; 

// sets the motor and arrow pins to output mode
void setup(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        pinMode(motors[i].e, OUTPUT);
        pinMode(motors[i].f, OUTPUT);
        pinMode(motors[i].r, OUTPUT);
        softPwmCreate(motors[i].e, 0, 100);
        digitalWrite(motors[i].e, HIGH);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
    }
    pinMode(arrows.af, OUTPUT);
    pinMode(arrows.ab, OUTPUT);
}

// sets all the motor and arrow pins to low and switches them into input mode
void cleanup(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        softPwmWrite(motors[i].e, 0);
        digitalWrite(motors[i].e, LOW);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
        pinMode(motors[i].e, INPUT);
        pinMode(motors[i].f, INPUT);
        pinMode(motors[i].r, INPUT);
    }

    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, LOW); 
    pinMode(arrows.af, INPUT); 
    pinMode(arrows.ab, INPUT);
}

// changes the duty_cycle to 0% and sets the forward and reverse pins to low
void stop(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d stops...\n", motors[i].num);
        softPwmWrite(motors[i].e, 0);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
    }

    // turns off the light of the arrows in the motorshield
    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, LOW); 

    // cleans up the pins when there is a keyboard interrupt and exits the program
    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

// sets the enable pin of the motors with the given duty_cycle 
// and sets the forward pin to high and the reverse pin to low
void forward(Motor motors[], int n, int duty_cycle, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d is moving forward with %d%% speed\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
        digitalWrite(motors[i].f, HIGH);
        digitalWrite(motors[i].r, LOW);
    }

    // lights up the forward arrow in the motorshield
    digitalWrite(arrows.af, HIGH); 
    digitalWrite(arrows.ab, LOW); 

    // cleans up the pins when there is a keyboard interrupt and exits the program
    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

// sets the enable pin of the motors with the given duty_cycle 
// and sets the forward pin to low and the reverse pin to high
void backward(Motor motors[], int n, int duty_cycle, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d is moving backward with %d%% speed\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, HIGH);
    }

    // lights up the backward arrow in the motorshield
    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, HIGH); 

    // cleans up the pins when there is a keyboard interrupt and exits the program
    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

// sets the enable pin of the motors with the given duty_cycle 
void change_speed(Motor motors[], int n, int duty_cycle) {
    for (int i = 0; i < n; i++) {
        printf("The speed of Motor%d is changing to %d%% speed\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
    }
}
