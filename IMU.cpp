#include "IMU.h"
#include "types.h"

#define DEBUG



void IMU::setupSensor()
{
    Wire.begin();

    mpu.initialize();
    mpu.setFullScaleAccelRange(0);

    if(!mpu.testConnection())
    {
        Serial.println("MPU6050 not available");
        while(1);
    } 
}






axes IMU::getAccelData()
{
    axes A;

    int16_t x,y,z;
    mpu.getAcceleration(&x,&y,&z);
    A.x = x/(float)offset;
    A.y = y/(float)offset;;
    A.z = z/(float)offset;;
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



