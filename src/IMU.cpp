#include "IMU.h"

// #define DEBUG



void IMU::setupSensor()
{
    Wire.begin();

    mpu.initialize();
    mpu.setFullScaleAccelRange(0);
    /**
     * sampleRate = 8kHz /(1 + SMPLRT_DIV)
     * for 50 Hz, SMPLRT_DIV should be 0x9F
    */
    mpu.setRate(0x9F);
    mpu.setIntDataReadyEnabled(true);

    if(!mpu.testConnection())
    {
        #ifdef DEBUG
            Serial.println("MPU6050 not available");
        #endif
        while(1);
    } 
}






axes IMU::getAccelData()
{
    axes A;

    int16_t x,y,z;
    while(!mpu.getIntDataReadyStatus());

    mpu.getAcceleration(&x,&y,&z);
    A.x = x/(float)offset;
    A.y = y/(float)offset;
    A.z = z/(float)offset;
    
    return A;
}

void IMU::fillBuffer(CB &buff)
{
    if(buff.isFull())
    {
        buff.push(getAccelData());
        return;
    }
    while(!buff.isFull())
    {
        buff.push(getAccelData());
    }
}



