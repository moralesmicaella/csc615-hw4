/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: Motor.h
*
* Description: This a header file that declares the variables
* and functions needed for the motors
******************************************************************/

#ifndef MOTOR_H
#define MOTOR_H
    typedef struct Motor {
        int num, e, f, r;
    } Motor;

    typedef struct Arrow {
        int af, ab;
    } Arrow;

    extern int keyboard_interrupt;
    extern Motor m1, m2;
    extern Arrow arrows;

    void setup(Motor motors[], int n, Arrow arrows);
    void cleanup(Motor motors[], int n, Arrow arrows);
    void stop(Motor motors[], int n, Arrow arrows);
    void forward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void backward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void change_speed(Motor motors[], int n, int duty_cycle);
#endif
