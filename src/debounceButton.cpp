#include "debounceButton.h"

BTN::BTN(uint8_t btnPin):btnPin{btnPin}
{
    pinMode(btnPin,INPUT_PULLUP);
    readBtn = digitalRead(btnPin);
}

bool BTN::pressed()
{   
    if(digitalRead(btnPin)) return false;
    
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