#ifndef ANALYZER_H_
#define ANALYZER_H_

#include "sTypes.h"

class Analyzer
{
    public:
        Analyzer(double *d);

        int getSteps(); 
        void updateSteps(int numberFromSet);
        int countSteps();





    private:
        uint8_t i = 0;
        unsigned long steps;
        bool countStep;
        double *data;
};




#endif