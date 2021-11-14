#include "UI.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setupScreen()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC)) 
    {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    display.invertDisplay(true);
    display.println(F("PEDOMETER"));
    display.display();
    display.clearDisplay();
    Serial.println("SCREEN SETUP DONE");
    delay(2000);
    display.invertDisplay(false);
}


void welcomeScreen()
{
    Serial.println(F("PEDO"));
    display.invertDisplay(true);
    display.println(F("PEDOMETER"));
    display.println(F("v 0.0.1"));
    display.println(F("2020"));
    display.display();
    display.setCursor(0,0);
    display.invertDisplay(false);
    delay(1500);
    
}