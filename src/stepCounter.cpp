/*


*/
#include <Arduino.h>

#include "IMU.h"
#include "filter.h"
#include "analyzer.h"

#define DEBUG

CB totalAccel; //raw data from IMU
CB gravityAccel; //lowpassed giving gravity acceleration
CB userAccel; //user acceleration


double dotP[maxSize];     //find dotP(movement in the direction of gravity)
double final[maxSize];
double magnitude[maxSize];

//IMU object
IMU imu;
Filter f;
Analyzer a(final);
// int i = 0;
// bool first = true;


void setup()
{
    Serial.begin(115200);
    
    imu.setupSensor();


}

void loop()
{  
    imu.fillBuffer(totalAccel);
    f.movingAverage(totalAccel,gravityAccel,WINDOW);
    f.getUserAccel(totalAccel,gravityAccel,userAccel);
    f.dotProduct(userAccel,gravityAccel,dotP);
    f.movingAverage(dotP,final,maxSize,WINDOW);

    #ifdef DEBUG
        Serial.println(a.getSteps());

    #endif

}
