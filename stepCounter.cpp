/*





*/
#include <Arduino.h>
// #include <FlashStorage_SAMD.h>
#include <vector>

#include "IMU.h"
#include "filter.h"
#include "analyzer.h"


#define SAMPLES 1500

// CB totalAccel; //raw data from IMU
// CB gravityAccel; //lowpassed giving gravity acceleration
// CB userAccel; //user acceleration


// double dotP[maxSize];     //find dotP(movement in the direction of gravity)
// double final[maxSize];

//IMU object
IMU imu;
// Filter f;
// Analyzer a(final);
// int i = 0;
// bool first = true;
std::vector<axes> store(SAMPLES);

void setup()
{
    Serial.begin(115200);
    Serial1.begin(9600);
    
    imu.setupSensor();

    // pinMode(LED_BUILTIN,OUTPUT);
    // Serial.println("10s to start reading");

    delay(10000);  //wait 10s to start attempting reading data

    for(int i = 0; i < SAMPLES;i++)
    {
        //store in SRAM
        store[i] = imu.getAccelData();

    }


    while (1)    //wait to connect back to PC to spew data
    {
        if((char)Serial1.read() == 'S')
        {
            break;
        }
    }
    Serial1.println();
    delay(1000);
    Serial1.println("About to spew...\n\n");
    Serial1.println("x\ty\tz");
    for(int i = 0; i < SAMPLES;i++)
    {
        //get data from SRAM
        Serial1.printf("%f\t%f\t%f\n",store[i].x,store[i].y,store[i].z);
        delay(1);
    }
    Serial1.println("\nDone spewing!");
}

void loop()
{  
    // imu.fillBuffer(totalAccel);
    // f.movingAverage(totalAccel,gravityAccel,WINDOW);
    // f.getUserAccel(totalAccel,gravityAccel,userAccel);
    // f.dotProduct(userAccel,gravityAccel,dotP);
    // f.movingAverage(dotP,final,maxSize,WINDOW);

    // a.countSteps();

    // i++;
    // if(i > maxSize - 1)
    // {
    //     i = 0;
    // }

    #ifdef DEBUG
        // Serial.print(i);TAB;
        Serial.print("x ");
        Serial.print(totalAccel[i].x);
         TAB;
        Serial.print("y ");
         Serial.print(totalAccel[i].y);
          TAB;
        Serial.print("z ");
         Serial.println(totalAccel[i].z);
         TAB;

        // // Serial.print("||Rx ");
        // Serial.println(smoothed[i].x);
        //  TAB;
        // // Serial.print("y ");
        //  Serial.println(smoothed[i].y);
        //  TAB;
        // // Serial.print("z ");
        //  Serial.print(gravityAccel[i].z);
        //  TAB; 

        // Serial.print("||Ux ");Serial.print(userAccel[i].x); TAB;
        // Serial.print("y "); Serial.print(userAccel[i].y); TAB;
        // Serial.print("z "); 
        // Serial.print(userAccel[i].z);
        // TAB;
        // Serial.print("1-D ");
        // Serial.print(dotP[i],6);
        // TAB;
        // Serial.print(final[i],6);
        // TAB;
        // // Serial.print("Number of Steps\t"); 
        Serial.println(a.getSteps());

    #endif

}
