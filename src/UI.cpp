#include "UI.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void UI::setupScreen()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC)) 
    {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_BLACK,SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
    display.println("PEDOMETER");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    Serial.println("SCREEN SETUP DONE");
    delay(1000);
}


void UI::welcomeScreen()
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

void UI::print(const char* text,int cursorPosX,int cursorPosY,int textSize,bool cls)
{
    if(cls) display.clearDisplay();
    display.setTextSize(textSize);
    display.setCursor(cursorPosX,cursorPosY);
    display.cp437(true);
    display.print(text);
    display.display();
}

void UI::menu()
{
    String steps = F("STEPS");
    String raw_data = F("RAW DATA");
    String help = F("HELP");

    if(currentPage != ePage::home)
        return;
    switch (selection)
    {
    case eMenuItem::steps:
        {
            display.clearDisplay();
            display.drawRect(0,0,SCREEN_WIDTH,14,SSD1306_WHITE);
            display.setTextSize(1);
            display.setCursor(5,4);
            display.cp437(true);
            display.print(steps);
            display.setCursor(5,18);
            display.print(raw_data);
            display.setCursor(5,32);
            display.print(help);
            display.display();
        }
        break;
    case eMenuItem::rawData:
        {
            display.clearDisplay();
            display.drawRect(0,15,SCREEN_WIDTH,14,SSD1306_WHITE);
            display.setTextSize(1);
            display.setCursor(5,4);
            display.cp437(true);
            display.print(steps);
            display.setCursor(5,18);
            display.print(raw_data);
            display.setCursor(5,32);
            display.print(help);
            display.display();
        }
        break;    
    case eMenuItem::off:
        {
            display.clearDisplay();
            display.drawRect(0,29,SCREEN_WIDTH,14,SSD1306_WHITE);
            display.setTextSize(1);
            display.setCursor(5,4);
            display.cp437(true);
            display.print(steps);
            display.setCursor(5,18);
            display.print(raw_data);
            display.setCursor(5,32);
            display.print(help);
            display.display();   
        }
        break;
    default:
        break;
    }    

    
}

void UI::showSteps(int numOfSteps)
{
    display.clearDisplay();
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xfff);
    display.setTextSize(1);
    display.setCursor(5,5);
    display.cp437(true);
    display.print("Number of Steps:\n");
    display.setCursor(5,15);
    display.setTextSize(2);
    display.print(numOfSteps);
    display.display();

}

void UI::showRawData(float x, float y, float z)
{
    display.clearDisplay();
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xfff);
    display.setTextSize(1);
    display.setCursor(5,5);
    display.cp437(true);
    display.print("Raw data(g):\n");
    display.setTextSize(2);
    display.printf("X: %f\nY: %f\nZ: %f",x,y,z);
    display.display();

}

void UI::moveMenu()
{
    if(selection == eMenuItem::steps)
    {
        selection = eMenuItem::rawData;
    }
    else if(selection == eMenuItem::rawData)
    {
        selection = eMenuItem::off;
    }
    else if(selection == eMenuItem::off)
    {
        selection = eMenuItem::steps;
    }
}

void UI::switchPage()
{
    if(selection == eMenuItem::steps)
    {
        currentPage = ePage::steps;
        showSteps(1);
    }
    else if(selection == eMenuItem::rawData)
    {
        currentPage = ePage::rawData;
        refreshPage();
    }
    else
    {
        currentPage = ePage::home;
    }
}
void UI::goHome()
{
    if(currentPage == ePage::steps || currentPage == ePage::rawData)
    {
        menu();
        currentPage = ePage::home;
    }
}

void UI::refreshPage()
{
    if(currentPage == ePage::rawData)
    {
        showRawData(1.f,1.f,1.f);
    }
    if(currentPage == ePage::steps)
    {
        showSteps(1);
    }
}