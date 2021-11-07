#include "analyzer.h"


Analyzer::Analyzer(double *d)
{
 steps = 0;  
 countStep = true; 
 data = d;
}

int Analyzer::countSteps()
{
        int lSteps=0;
        i++;
        int cur = i%maxSize;
        int prev = (i-1)%maxSize;
        // Serial.printf("CountSteps:: cur %d, prev %d. i %d\n",cur,prev,i);

    if((data[cur] >= THRESHOLD) && (data[prev]) < THRESHOLD)
    {
        if(!countStep) return 0;
        lSteps++;
        countStep = false;
        return lSteps;
    }
    if((data[cur] < 0) && (data[prev] >= 0))
        {countStep = true;}
    return lSteps;
}

void Analyzer::updateSteps(int numberFromSet)
{
    steps += numberFromSet;
}

int Analyzer::getSteps()
{
    updateSteps(countSteps());
    return steps;
}