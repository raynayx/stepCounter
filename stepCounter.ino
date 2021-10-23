/*





*/
#include <FlashStorage_SAMD.h>

#include "IMU.h"
#include "filter.h"
#include "analyzer.h"

// #define DEBUG

#define EEPROM_EMULATION_SIZE     (100 * 1024)
#define FLASH_DEBUG       2


CB totalAccel; //raw data from IMU
CB gravityAccel; //lowpassed giving gravity acceleration
CB userAccel; //user acceleration


double dotP[maxSize];     //find dotP(movement in the direction of gravity)
double final[maxSize];

//IMU object
IMU imu;
// Filter f;
// Analyzer a(final);
// int i = 0;
// bool first = true;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(9600);
    
    imu.setupSensor();

    Serial.print("EEPROM length: ");
    Serial.println(EEPROM.length());
    

    delay(10000);  //wait 10s to start attempting reading data
    uint16_t addr = 0;
    axes accel;

    for(int i = 0; i < 8500;i++)
    {
        accel = imu.getAccelData();
        //write to flash
        EEPROM.put(addr,accel);
        addr += 13; 
    }

    if(!EEPROM.getCommitASAP())
    {
        Serial.println("need commit()");
        EEPROM.commit();
    }







    while (!Serial1); //wait to connect back to PC to spew data
    delay(5000);
    accel = {0};
    addr = 0;
    Serial1.println("About to spew...");
    for(int i = 0; i < 8500;i++)
    {
        //get data from flash
        EEPROM.get(addr,accel);
        Serial1.print(accel.x); TAB;
        Serial1.print(accel.y);TAB;
        Serial1.println(accel.z);
        delay(500);
        addr += 13; 
    }
    Serial1.println("Done spewing!");
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
