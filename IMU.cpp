#include "IMU.h"
#include "types.h"

#define DEBUG



void IMU::setupSensor()
{
    Wire.begin();

    mpu.initialize();

    if(!mpu.testConnection())
    {
        Serial.println("MPU6050 not available");
        while(1);
    } 
}






axes IMU::getAccelData()
{
    axes A;

    int16_t a,b,c;
    mpu.getAcceleration(&a,&b,&c);
    A.x = a;
    A.y = b;
    A.z = c;
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



