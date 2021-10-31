/*
************ LSM9DS1 IMU over I2C ************

LSM9DS1 --------- XIAO
SCL ---------- SCL (5)
SDA ---------- SDA (4)
VDD ------------- 3V3
GND ------------- GND

**********************************************

************ LSM9DS1 IMU over SPI ************

LSM9DS1 --------- XIAO
CS_AG ---------- 3
CS_M ---------- 2
SDO_M ------------ 9
SDO_AG ----------- 9
VDD -------------- 3V3
GND -------------- GND

**********************************************

*/
#ifndef IMU_H_
#define IMU_H_


#include "MPU6050.h" 
#include "types.h"

 
class IMU
{
    public:
           

        //setup the range and other parameters of the sensor
        void setupSensor();

        //configure interrupts
        void configureLSM9DS1Interrupts();
        // get accel data
        axes getAccelData();
        //fill buffer
        void fillBuffer(CB &buff);
        

    private:  
        //default I2C address is 0x68; 
        MPU6050 mpu;

        const int offset = 16384;

          
};

#endif