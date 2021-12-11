/*


*/
#include <Arduino.h>

#include "UI.h"
#include "IMU.h"
#include "filter.h"
#include "analyzer.h"
#include "debounceButton.h"


// #define DEBUG

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
UI u;

/**
 * Buttons
 * 
 * 
 * */
const uint8_t navBtn = 7;
const uint8_t selBtn = 6;
// BTN nav;

bool navBtnLastState = HIGH;
bool selBtnLastState = HIGH;
bool navBtnState;
bool selBtnState;

unsigned long navLastDebounce = 0;
unsigned long selLastDebounce = 0;
unsigned long lastScreenOff = 0;
uint8_t debounceDelay = 50;
uint16_t screenOffTime = 10000;

 
void setup()
{
    Serial.begin(115200);
    pinMode(navBtn,INPUT_PULLUP);
    pinMode(selBtn,INPUT_PULLUP);
    // nav.init(navBtn);
    imu.setupSensor();
    u.setupScreen();
    u.welcomeScreen();

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

    uint8_t readNavBtn = digitalRead(navBtn);
    uint8_t readSelBtn = digitalRead(selBtn);

    // if(nav.pressed())
    // {
    //     Serial.print("Nav pressed");
    // }
    if(readNavBtn != navBtnLastState)
    {
        navLastDebounce = millis();
    }
    if(readSelBtn != selBtnLastState)
    {
        selBtnLastState = millis();
    }

    if((millis() - navLastDebounce) > debounceDelay )
    {
        if(readNavBtn != navBtnState)
        {
            navBtnState = readNavBtn;

            if(navBtnState == LOW)
            {
                if(!u.screenState) u.screenOn();
                u.moveMenu();
                u.goHome();
                lastScreenOff = millis();
            }
        }
    }

    if((millis() - selLastDebounce) > debounceDelay )
    {
        if(readSelBtn != selBtnState)
        {
            selBtnState = readSelBtn;

            if(selBtnState == LOW)
            {
                u.switchPage();
                lastScreenOff = millis();
            }
        }
    }
    navBtnLastState = readNavBtn;
    selBtnLastState = readSelBtn;
    u.menu();
    u.showPage(imu.getAccelData(),a.getSteps());

    if(millis() - lastScreenOff > screenOffTime)
    {
        u.screenOff();
    }

}
