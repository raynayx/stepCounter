/**
* Using Moving Average to Filter the total
acceleration to get the acceleration due to gravity
* Subtract the acceleration due to gravity from
the total acceleration to get the user acceleration
* Find dot product to get 1-D acceleration 
(Isolate movement in the direction of gravity)
*/

#ifndef FILTER_H_
#define FILTER_H_

#include "types.h"

class Filter
{
    public:
        
        void movingAverage(axes* X,axes* Y,int size,int window);
        void movingAverage(CB& X,CB& Y,int window);
        void getUserAccel(axes* totalAccel,axes* gravityAccel,axes* userAccel,int size);
        void getUserAccel(CB& totalAccel,CB& gravityAccel,CB& userAccel);
        void dotProduct(axes* userAccel, axes* gravityAccel,double *dp,int size);
        void dotProduct(CB &userAccel,CB &gravityAccel,double *dp);
        void movingAverage(double *X,double *Y, int size,int window);

    private:
        bool first = true;

};



#endif