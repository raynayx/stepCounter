#include "analyzer.h"


Analyzer::Analyzer(double *d)
{
 steps = 0;  
 countStep = true; 
 data = d;
}

int Analyzer::getSteps()
{
    return steps;
}

// void Analyzer::updateSteps(int numberFromSet)
// {
//     steps += numberFromSet;
// }

int Analyzer::countSteps()
{
    for(int i = 1; i < maxSize; i++)
    {

    if((data[i] >= THRESHOLD) && (data[i-1]) < THRESHOLD)
    {
        if(!countStep)
            continue;       
        steps++;
        countStep = false;
    }
    if((data[i] < 0) && (data[i-1] >= 0))
        countStep = true;

        
    }
    return steps;
}