#include "micromouse.h"
#include <Encoder.h>
#include <MPU6050.h>

/*Encoder objects*/
Encoder right_encoder(ENCODER_0_CHA, ENCODER_0_CHB);
Encoder left_encoder(ENCODER_1_CHA, ENCODER_1_CHB);

/*MPU6050 gyro object*/
MPU6050 gyro;

void motors_init(void)
{
  pinMode(ENABLE, OUTPUT);
  pinMode(MOTOR_0_1A, OUTPUT);
  pinMode(MOTOR_0_2A, OUTPUT);
  pinMode(MOTOR_1_1A, OUTPUT);
  pinMode(MOTOR_1_2A, OUTPUT);

  /*Enable motors by default*/
  digitalWrite(ENABLE, HIGH);
}
  
void motor_0_speed(int speed, bool direction)
{
  if(direction == true)
  {
    /*Move motor forward at given speed*/
    analogWrite(MOTOR_0_1A, 0);
    analogWrite(MOTOR_0_2A, speed);
  }
  else
  {
    analogWrite(MOTOR_0_1A, speed);
    analogWrite(MOTOR_0_2A, 0);
  }
}

void motor_1_speed(int speed, bool direction)
{
  if(direction == true)
  {
    /*Move motor forward at given speed*/
    analogWrite(MOTOR_1_1A, speed);
    analogWrite(MOTOR_1_2A, 0);
  }
  else
  {
    analogWrite(MOTOR_1_1A, 0);
    analogWrite(MOTOR_1_2A, speed);
  }
}

void ir_init(void)
{
  pinMode(IR0_TX, OUTPUT);
  pinMode(IR1_TX, OUTPUT);
  pinMode(IR2_TX, OUTPUT);
  pinMode(IR3_TX, OUTPUT);

  /*Initalize to low state*/
  digitalWrite(IR0_TX, LOW);
  digitalWrite(IR1_TX, LOW);
  digitalWrite(IR2_TX, LOW);
  digitalWrite(IR3_TX, LOW);
}

int ir_0_read(int delay)
{
  if(delay > 150)
  {
    delay = 150;
  }
  
  digitalWrite(IR0_TX, HIGH);
  delayMicroseconds(delay);
  int value = analogRead(IR0_RX);
  digitalWrite(IR0_TX, LOW);

  return value; 
}

int ir_1_read(int delay)
{
  if(delay > 150)
  {
    delay = 150;
  }
  
  digitalWrite(IR1_TX, HIGH);
  delayMicroseconds(delay);
  int value = analogRead(IR1_RX);
  digitalWrite(IR1_TX, LOW);

  return value; 
}

int ir_2_read(int delay)
{
  if(delay > 150)
  {
    delay = 150;
  }
  
  digitalWrite(IR2_TX, HIGH);
  delayMicroseconds(delay);
  int value = analogRead(IR2_RX);
  digitalWrite(IR2_TX, LOW);

  return value; 
}

int ir_3_read(int delay)
{
  if(delay > 150)
  {
    delay = 150;
  }
  
  digitalWrite(IR3_TX, HIGH);
  delayMicroseconds(delay);
  int value = analogRead(IR3_RX);
  digitalWrite(IR3_TX, LOW);

  return value; 
}

void gyro_init(void)
{
  gyro.initialize();
  gyro.CalibrateGyro();
}

float get_angle(float dt)
{
  int16_t raw_yaw_rate = gyro.getRotationZ();
  float yaw_rate = (float)raw_yaw_rate / 131.0;
  float yaw_angle = yaw_rate * dt;

  return yaw_angle;
}

/*Control functions**********************************/
/*Forward Control***********************************/
const int RIGHT_IR_THRESHOLD = 200;
const int LEFT_IR_THRESHOLD = 200; 
const long int MIN_ERROR = 50;
const long int target_distance = 1090;
const float distance_kp = 1.0;
const float speed_kp = 2.0;
const float ir_kp = 2.0;

float clamp(float value, float max, float min)
{
  if(value > max)
  {
    value = max;
  }
  else if(value < min)
  {
    value = min;
  }

  return value;
}

bool find_direction(int value)
{
  bool dir;
  if(value > 0)
  {
    dir = true;
  }
  else if(value < 0)
  {
    dir = false;
  }
  return dir;
}

void control_forward(void)
{
    /*Keep running the control loop until the error is less that the 
   * minimum specified error (MIN_ERROR)
   */
  int distance_error;  
  do
  {
    /*Read encoder for left and right motors. Estimate
     * mouse traveled distance by taking the average of
     * both encoders.
     */
    long int r_count = right_encoder.read();
    long int l_count = -left_encoder.read();
    long int encoder_distance = (r_count + l_count) / 2;

    /*Read infrared sensors. Ideally both infrared sensors
     * should read the same value form the wall, so for our error
     * we can do r_infrared - l_infrared. Check if there is no wall
     * one side or the other since this will cause the mouse go towards one wall
     */
    int r_ir = ir_1_read(150);
    int l_ir = ir_2_read(150);

    if(r_ir < RIGHT_IR_THRESHOLD)
    {
      /*force "good measurement*/
      r_ir = 700;
    }
    if(l_ir < LEFT_IR_THRESHOLD)
    {
      /*force "good measurement*/
      l_ir = 700;
    }
  
    /*Compute distance, speed mismatch and distance from wall error*/
    distance_error = target_distance - encoder_distance;
    int mismatch_error = r_count - l_count;
    int ir_error = r_ir - l_ir;
    
    /*Proportional error for all of our errors. Clamp values for all outputs
    Check the function clamp*/
    float distance_output = clamp(distance_kp*distance_error, 150.0, -150.0);
    float mismatch_output = clamp(speed_kp*mismatch_error, 50.0, -50.0);
    float ir_output = clamp(ir_kp*ir_error, 50.0, -50.0);
        
    /*Calculate final output speed for each wheel*/
    int left_output = ((int)distance_output + (int)(mismatch_output) - (int)(ir_output)); 
    int right_output = ((int)distance_output - (int)(mismatch_output) + (int)(ir_output));

    /*Find the turn direction of each wheel. Check the find_direction function*/
    bool left_dir = find_direction(left_output);
    bool right_dir = find_direction(right_output);
    
    motor_0_speed(abs(right_output), right_dir);
    motor_1_speed(abs(left_output), left_dir);
    
    delay(20);
  }while(abs(distance_error) > MIN_ERROR);

  /*Stop both motors*/
  motor_0_speed(0, true);
  motor_1_speed(0, true);

  /*Reset encoders*/
  right_encoder.write(0);
  left_encoder.write(0);
}

/*Turn Control***********************************/
const float MIN_TURN_ERROR = 1.0;
const float turn_kp = 30.0;

void control_turn(float target_angle)
{
   /*Keep running the control loop until the error is less that the 
   * minimum specified error (MIN_TURN_ERROR)
   */
  float yaw_angle = 0.0;
  float dt = 0.0;
  float t0;
  float turn_error;
  do
  {
    t0 = millis() / 1000.0;
    
    /*Read gyro yaw angle, remember that this is a measurement for
     * this time period so we need to sum the previous angle measurements
     */
    yaw_angle += get_angle(dt);
  
    /*Compute turn error*/
    turn_error = target_angle - yaw_angle;
    
    /*Proportional error for turn. Clamp output value*/
    float turn_output = clamp(turn_kp*turn_error, 80.0, -80.0);
        
    /*Calculate final output speed for each wheel*/
    int left_output = (int)(-turn_output); 
    int right_output = (int)(turn_output);

    /*Find the turn direction of each wheel. Check the find_direction function*/
    bool left_dir = find_direction(left_output);
    bool right_dir = find_direction(right_output);
    
    /*Set speed and direction to motors*/
    motor_0_speed(abs(right_output), right_dir);
    motor_1_speed(abs(left_output), left_dir);

    /*delay the control loop and calculate delta time*/
    delay(50);
    dt = millis()/1000.0 - t0;
  }while(fabs(turn_error) > MIN_TURN_ERROR);

  /*Stop both motors*/
  motor_0_speed(0, true);
  motor_1_speed(0, true);
}
