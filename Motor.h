/******************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Micaella Morales
* Student ID: 916832064
* Project: Assignment 4 - Motors & Speed Encoder
* File: Motor.h
*
* Description:
* 
******************************************************************/

#ifndef MOTOR_H
#define MOTOR_H
    extern int keyboard_interrupt;

    typedef struct Motor {
        int num, e, f, r;
    } Motor;

    typedef struct Arrow {
        int af, ar;
    } Arrow;

    int setup(Motor motors[], int n, Arrow arrows);
    void cleanup(Motor motors[], int n, Arrow arrows);
    void stop(Motor motors[], int n, Arrow arrows);
    void forward(Motor motors[], int n, int speed, Arrow arrows);
    void backward(Motor motors[], int n, int speed, Arrow arrows);
    void change_speed(Motor motors[], int n, int speed);
#endif
