/*





*/
#include "IMU.h"
#include "filter.h"
#include "analyzer.h"
#include <CircularBuffer.h>

#define DEBUG

axes samples[maxSize];    //new data set in circular buffer
axes result[maxSize] = {0};   // result from moving average
axes userAccel[maxSize];
double dotP[maxSize];     //find dotP(movement in the direction of gravity)
// axes ones = {1.0,1.0,1.0};

//IMU object
IMU imu;
Filter f;
Analyzer a(dotP);
int i = 0;
bool first = true;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN,OUTPUT);
    imu.setupSensor();
     //fill buffer
     for(int i = 0;i < maxSize; i++)
    {
        samples[i] = imu.getAccelData();
        // samples[i] = ones;
    }

}

void loop()
{   
    f.movingAverage(samples,result,maxSize,WINDOW);
    f.getUserAccel(samples,result,userAccel,maxSize);
    f.dotProduct(userAccel,result,dotP,maxSize);
    a.countSteps();

    i++;
    if(i > maxSize - 1)
    {
        i = 0;
    }

    #ifdef DEBUG
        // Serial.print(i);TAB; Serial.print("x ");Serial.print(samples[i].x); TAB;
        // Serial.print("y "); Serial.print(samples[i].y); TAB;
        // Serial.print("z "); Serial.print(samples[i].z); TAB;

        // Serial.print("||Rx ");Serial.print(result[i].x); TAB;
        // Serial.print("y "); Serial.print(result[i].y); TAB;
        // Serial.print("z "); Serial.print(result[i].z);TAB; 

        // Serial.print("||Ux ");Serial.print(userAccel[i].x); TAB;
        // Serial.print("y "); Serial.print(userAccel[i].y); TAB;
        // Serial.print("z "); Serial.print(userAccel[i].z);TAB;
        Serial.print("1-D ");Serial.println(dotP[i]);
        Serial.print("Number of Steps\t"); Serial.println(a.getSteps());

    #endif
    samples[i] = imu.getAccelData();
}
