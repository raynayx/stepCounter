#ifndef TYPES_H_
#define TYPES_H_

#include <Arduino.h>

#define maxSize 119
#define THRESHOLD 0.35
#define WINDOW 5


#define TAB Serial.print(F("\t"))

struct axes
{
    float x = 0.0; 
    float y = 0.0; 
    float z = 0.0;
};

struct COEFFICIENTS
{
    double alpha[3];
    double beta[3];
};




#endif