#ifndef TYPES_H_
#define TYPES_H_

#include <Arduino.h>
#include <CircularBuffer.h>


#define maxSize 50
#define THRESHOLD 0.1
#define WINDOW 3


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

typedef CircularBuffer<axes,maxSize> CB;
extern CB buffer;



#endif