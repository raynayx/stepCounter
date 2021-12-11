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
    delay(100);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    delay(100);
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
    delay(700);
    
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
    String off = F("TURN OFF SCREEN");

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
            display.setCursor(5,46);
            display.print(off);
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
            display.setCursor(5,46);
            display.print(off);
            display.display();
        }
        break;    
    case eMenuItem::help:
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
            display.setCursor(5,46);
            display.print(off);
            display.display();
        }
        break;
        case eMenuItem::off:
        {
            display.clearDisplay();
            display.drawRect(0,43,SCREEN_WIDTH,14,SSD1306_WHITE);
            display.setTextSize(1);
            display.setCursor(5,4);
            display.cp437(true);
            display.print(steps);
            display.setCursor(5,18);
            display.print(raw_data);
            display.setCursor(5,32);
            display.print(help);
            display.setCursor(5,46);
            display.print(off);
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
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
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
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(5,5);
    display.cp437(true);
    display.print("Raw data(g):\n");
    display.setTextSize(1);
    display.setCursor(5,15);
    display.printf("X: %f",x);
    display.setCursor(5,30);
    display.printf("Y: %f",y);
    display.setCursor(5,45);
    display.printf("Z: %f",z);
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
        selection = eMenuItem::help;
    }
    else if(selection == eMenuItem::help)
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
    }
    else if(selection == eMenuItem::rawData)
    {
        currentPage = ePage::rawData;
    }
    else if(selection == eMenuItem::help)
    {
        currentPage = ePage::help;
    }
    else if(selection == eMenuItem::off)
    {
        screenOff();
    }
}
void UI::goHome()
{
    if(currentPage == ePage::steps || currentPage == ePage::rawData || currentPage == ePage::help)
    {
        menu();
        currentPage = ePage::home;
    }
}

void UI::showPage(axes rawData,int steps)
{
    switch (currentPage)
    {
    case ePage::steps:
    {
        showSteps(steps);
        break;
    }
    case ePage::rawData:
    {
        showRawData(rawData.x,rawData.y,rawData.z);
        break;
    }
    case ePage::help:
    {
        showHelp();
        break;
    }
    default:
        break;
    }
}

void UI::showHelp()
{
    display.clearDisplay();
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(5,5);
    display.cp437(true);
    display.print("HELP");
    display.setTextSize(1);
    display.setCursor(5,15);
    display.print(F("Welcome to Pedometer"));
    display.setCursor(5,25);
    display.print(F("help.Since you are"));
    display.setCursor(5,35);
    display.print(F("here, you know how   to move. Bye bye!"));
    display.display();
}


void UI::screenOff()
{
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    screenState = false;

}
void UI::screenOn()
{
    display.ssd1306_command(SSD1306_DISPLAYON);
    screenState = true;
}