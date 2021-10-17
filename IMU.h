/*
************ LSM9DS1 IMU over I2C ************

LSM9DS1 --------- XIAO
SCL ---------- SCL (5)
SDA ---------- SDA (4)
VDD ------------- 3V3
GND ------------- GND

**********************************************
*/
#ifndef IMU_H_
#define IMU_H_

#include "types.h"
#include <Wire.h>
#include <SparkFunLSM9DS1.h>
 
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
        //LSM9DS1 IMU declaration
        LSM9DS1 lsm;    
};

#endif