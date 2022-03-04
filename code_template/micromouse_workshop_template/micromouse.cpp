#include "micromouse.h"

/*YOU MUST INSTALL MPU6050 LIBRARY FOR THIS PORTION OF THE CODE!*/
//#include <MPU6050.h>
//MPU6050 gyro; 

/*YOU MUST INSTALL ENCODER LIBRARY BY PAUL STOFFREGEN*/
//#include <Encoder.h>

//Encoder right_encoder(ENCODER_0_CHA, ENCODER_0_CHB);
//Encoder left_encoder(ENCODER_1_CHA, ENCODER_1_CHB); 

/*Motors  Code******************/
void motors_init(void)
{

}
  
void motor_0_speed(int speed, bool direction)
{

}

void motor_1_speed(int speed, bool direction)
{

}

/*Infrared Sensors Code******************/
void ir_init(void)
{

}

int ir_0_read(int delay)
{
 
}

int ir_1_read(int delay)
{
 
}

int ir_2_read(int delay)
{

}

int ir_3_read(int delay)
{
 
}

/*Gyroscope sensor code*******************/
void gyro_init(void)
{
  
}

float gyro_get_yaw(float dt)
{
  
}

/*Control loop code**********************/
void control_forward(void)
{
    
}  

void control_turn(float target_angle)
{
    
}
