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

    // 2. speed control ----------------------------------------------------------
    printf("\n\n 2. speed control\n");

    //jobs to be done beforehand;
    PositionControlOnOff_Write(UNCONTROL); // position controller must be OFF !!!

    //control on/off
    status=SpeedControlOnOff_Read();
    printf("SpeedControlOnOff_Read() = %d\n", status);
    SpeedControlOnOff_Write(CONTROL);

    //speed controller gain set
    //P-gain
    gain = SpeedPIDProportional_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDProportional_Read() = %d \n", gain);
    gain = 20;
    SpeedPIDProportional_Write(gain);

    //I-gain
    gain = SpeedPIDIntegral_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDIntegral_Read() = %d \n", gain);
    gain = 20;
    SpeedPIDIntegral_Write(gain);
    
    //D-gain
    gain = SpeedPIDDifferential_Read();        // default value = 10, range : 1~50
    printf("SpeedPIDDefferential_Read() = %d \n", gain);
    gain = 20;
    SpeedPIDDifferential_Write(gain);

    //speed set    
    speed = DesireSpeed_Read();
    printf("DesireSpeed_Read() = %d \n", speed);
    speed = -10;
    DesireSpeed_Write(speed);
 
    sleep(2);  //run time 

    speed = DesireSpeed_Read();
    printf("DesireSpeed_Read() = %d \n", speed);

    speed = 0;
    DesireSpeed_Write(speed);
    sleep(1);

    return 0;
}
