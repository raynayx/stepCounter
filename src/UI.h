#ifndef UI_H_
#define UI_H_

#include "sTypes.h"


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI   10
#define OLED_CLK   8
#define OLED_DC    0
#define OLED_CS    12
#define OLED_RESET 1



extern Adafruit_SSD1306 display;


class UI
{
    private:
        enum class eMenuItem {steps,rawData,help,off};
        enum class ePage {home,steps,rawData,help};

        eMenuItem selection = eMenuItem::steps;
        ePage currentPage = ePage::home;

    public:
        bool screenState = true;
        void setupScreen();
        void welcomeScreen();
        void menu();
        void moveMenu();
        void switchPage();
        void showPage(axes rawData,int steps);
        void goHome();
        void screenOn();
        void screenOff();
        void print(const char* text,int cursorPosX,int cursorPosY,int textSize,bool cls);
        void showSteps(int numOfSteps);
        void showRawData(float x,float y, float z);
        void showHelp();
};

#endif