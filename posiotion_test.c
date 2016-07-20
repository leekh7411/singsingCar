// gcc main.c -o main

#include <stdio.h>
#include <stdlib.h>
#include "car_lib.h"

#define LIGHT_BEEP       // to test light and beep
#define SPEED_CONTROL     // to test speed control
#define POSITION_CONTROL  // to test postion control
#define SERVO_CONTROL     // to test servo control(steering & camera position)
#define LINE_TRACE              // to test line trace sensor
#define DISTANCE_SENSOR     // to test distance sensor

int main(void)
{
    unsigned char status;
    short speed;
    unsigned char gain;
    int position, position_now;
    short angle;
    int channel;
    int data;
    char sensor;
    int i, j;
    int tol;
    char byte = 0x80;

    CarControlInit();

    // 1. position control -------------------------------------------------------
    printf("\n\n 1. position control\n");

    //jobs to be done beforehand;
    SpeedControlOnOff_Write(CONTROL);   // speed controller must be also ON !!!
    speed = 50; // speed set     --> speed must be set when using position controller
    DesireSpeed_Write(speed);

    //control on/off
    status = PositionControlOnOff_Read();
    printf("PositionControlOnOff_Read() = %d\n", status);
    PositionControlOnOff_Write(CONTROL);

    //position controller gain set
    gain = PositionProportionPoint_Read();    // default value = 10, range : 1~50
    printf("PositionProportionPoint_Read() = %d\n", gain);
    gain = 20;
    PositionProportionPoint_Write(gain);
            
    //position write
    position_now = 0;  //initialize
    EncoderCounter_Write(position_now);
    
    //position set
    position=DesireEncoderCount_Read();
    printf("DesireEncoderCount_Read() = %d\n", position);
    position = 600;
    DesireEncoderCount_Write(position);

    position=DesireEncoderCount_Read();
    printf("DesireEncoderCount_Read() = %d\n", position);
    
    int accel = 0;
    tol = 10;    // tolerance
    while(position_now < 1000)
    {
        if(accel <= 20){
        	speed++;
        	DesireSpeed_Write(speed);
        	accel++;
        }else if(accel > 20){
        	speed--;
        	DesireSpeed_Write(speed);
        	accel--;
        }
        position_now=EncoderCounter_Read();
        printf("EncoderCounter_Read() = %d\n", position_now);
    }
    sleep(1);

    return 0;

}
