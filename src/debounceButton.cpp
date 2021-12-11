#include "debounceButton.h"

void BTN::init(uint8_t btnPin)
{
    pinMode(btnPin,INPUT_PULLUP);
    readBtn = digitalRead(btnPin);
}

bool BTN::pressed()
{   
    readBtn = digitalRead(btnPin);
    if(readBtn) 
    {
        btnLastState = readBtn;
        return false;
    }
    if(digitalRead(btnPin) != btnLastState)
    {
        btnDebounce = millis();
    }

    if((millis() - btnDebounce) >= debounceDelay )
    {
        if(digitalRead(btnPin) != btnState)
        {
            btnState = digitalRead(btnPin);

            if(btnState == LOW)
            {
                btnLastState = digitalRead(btnPin);
                return true;
            }
        }
    }
    btnLastState = digitalRead(btnPin);
    return false;
}