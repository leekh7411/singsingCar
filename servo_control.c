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
unsigned char status;
short speed;
unsigned char gain;
int position, position_now;
//short angle;
int channel;
int data;
char sensor;
int i, j;
int tol;
char byte = 0x80;
int angle = 1500;

void position_config();

void servo_control(int angle);
int control_position(int position);

int main(void)
{

    //Test Change

    CarControlInit();

    servo_control(1500);

    position_config();

    //servo_control();
    

    return 0;
}

void position_config(){

    int accel = 0;
    tol = 10;  // tolerance
    
    printf("\n\n 1. position control\n");

    //jobs to be done beforehand;
    SpeedControlOnOff_Write(CONTROL);   // speed controller must be also ON !!!
    speed = 25; // speed set     --> speed must be set when using position controller
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

    int pos = 600;
    control_position(pos);

    int next_start = 0;
    
    while(1){
        sleep(1);
        printf("In sleep...", gain);
        
        if(abs(position_now-pos)<=tol){
            next_start = 1;
            break;
        }
    }   


    if(next_start == 1){
        control_position(-600);
    }
    
    
    
    position=DesireEncoderCount_Read();
    printf("DesireEncoderCount_Read() = %d\n", position);


    
    
    
    //PositionControlOnOff_Write(UNCONTROL); // position controller must be OFF !!!
}

int control_position(int pos){
    //position write
    position_now = 0;  //initialize
    EncoderCounter_Write(position_now);
    
    //position set
    position=DesireEncoderCount_Read();
    printf("DesireEncoderCount_Read() = %d\n", position);
    //pos = -600;
    DesireEncoderCount_Write(pos);

    while(abs(position_now-pos)>tol)
    {

        position_now=EncoderCounter_Read();
        printf("EncoderCounter_Read() = %d\n", position_now);
    } 

    return 0;     
    
}


void servo_control(int _angle){
    SteeringServoControl_Write(_angle);
    CameraXServoControl_Write(_angle);
    //CameraYServoControl_Write(angle); 
    
}