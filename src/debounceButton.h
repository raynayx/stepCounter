#ifndef _DEBOUNCE_BUTTON_
#define _DEBOUNCE_BUTTON_ 
#include <Arduino.h>

class BTN
{
    public:
        void init(uint8_t btnPin);
        bool pressed();
    private:
        bool btnLastState = HIGH;
        bool btnState;

        unsigned long btnDebounce = 0;
        uint8_t debounceDelay = 20;
        uint8_t readBtn;
        uint8_t btnPin;
};


#endif