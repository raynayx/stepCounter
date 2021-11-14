#ifndef UI_H_
#define UI_H_


#include "sTypes.h"


#include <SPI.h>
#include <Wire.h>
// #include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI   10
#define OLED_CLK   8
#define OLED_DC    0
#define OLED_CS    12
#define OLED_RESET 1



enum class menuItem {steps,rawData,off};
enum class page {home,steps,rawData};
void setupScreen();
void welcomeScreen();
void menu();
void moveMenu();
void switchPage();
void refreshPage();
void goHome();
void screenOn();
void screenOff();



#endif