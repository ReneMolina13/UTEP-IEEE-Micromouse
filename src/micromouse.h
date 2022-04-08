#ifndef MICROMOUSE_H_
#define MICROMOUSE_H_

#include <Arduino.h>
#include <stdbool.h>

/*Motor definitions*/
#define ENABLE            A6
#define MOTOR_0_1A        11
#define MOTOR_0_2A        5
#define MOTOR_1_1A        6  
#define MOTOR_1_2A        9
#define ENCODER_0_CHA     2
#define ENCODER_0_CHB     13
#define ENCODER_1_CHA     3
#define ENCODER_1_CHB     8

/*Infrared sensors definitions*/
#define IR0_TX       A1
#define IR1_TX       12
#define IR2_TX       7
#define IR3_TX       4
#define IR0_RX       A0
#define IR1_RX       A7
#define IR2_RX       A2
#define IR3_RX       A3

/*Extras*/
#define BUTTON      10

void motors_init(void);
void motor_0_speed(int speed, bool direction);
void motor_1_speed(int speed, bool direction);

void ir_init(void);
int ir_0_read(int delay);
int ir_1_read(int delay);
int ir_2_read(int delay);
int ir_3_read(int delay);

void gyro_init(void);
float gyro_get_yaw(float dt);

void control_forward(void);
void control_turn(float target_angle);

#endif
