#ifndef UI_H_
#define UI_H_

/*
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





class UI
{
    private:
        // const uint8_t SCREEN_WIDTH = 128; // OLED display width, in pixels
        // const uint8_t SCREEN_HEIGHT = 64; // OLED display height, in pixels

        // const uint8_t OLED_MOSI = 10;
        // const uint8_t OLED_CLK  = 8;
        // const uint8_t OLED_DC  = 0;
        // const uint8_t OLED_CS  = 12;
        // const uint8_t OLED_RESET = 1;


        enum class menuItem {steps,rawData,off};
        enum class page {home,steps,rawData};

    public:
    
        Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

        void setupScreen();
        void welcomeScreen();
        void menu();
        void moveMenu();
        void switchPage();
        void refreshPage();
        void goHome();
        void screenOn();
        void screenOff();
};
*/
#endif