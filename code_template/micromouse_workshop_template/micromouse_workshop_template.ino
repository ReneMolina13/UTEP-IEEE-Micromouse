#include "micromouse.h"

void setup() 
{
    motors_init();
    gyro_init();
    ir_init();
    
    /*Enable serial port for bluetooth*/
    Serial.begin(9600);
}

void loop() 
{
    /*Main micromouse code here*/
}
