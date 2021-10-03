#ifndef ANALYZER_H_
#define ANALYZER_H_

#include "types.h"

class Analyzer
{
    public:
        Analyzer(double *d);

        int getSteps(); 
        // void updateSteps(int numberFromSet);
        int countSteps();





    private:
        unsigned long steps;
        bool countStep;
        double *data;
};




#endif