#include "filter.h"
/**
 * Input signal is X
 * Output signal is Y
 * The window size is window
 * 
 * 
 * 
*/
void Filter::movingAverage(axes* X,axes* Y,int size,int window)
{
    for (int i = 0; i < window - 1; i++)
    {
        Y[i].x = 0.0;
        Y[i].y = 0.0;
        Y[i].z = 0.0;
    }

    for (int i = window - 1; i < size ; i++)
    {
        axes sum = {0.0,0.0,0.0};
        for (int j = 0; j < window ; j++)
        {
            sum.x += X[i - j].x;
            sum.y += X[i - j].y;
            sum.z += X[i - j].z;
        }
        Y[i].x = (sum.x) / (float)window;
        Y[i].y = (sum.y) / (float)window;
        Y[i].z = (sum.z) / (float)window;
    }
}

/**
 * totalAccel is the original data from IMU
 * gravityAccel is the result of running a moving average filter on the total accel
 * userAccel is the difference (totalAccel - gravityAccel) 
*/
void Filter::getUserAccel(axes* totalAccel,axes* gravityAccel,axes* userAccel,int size)
{
    for(int i = 0; i < size; i++)
    {
        userAccel[i].x = totalAccel[i].x - gravityAccel[i].x;
        userAccel[i].y = totalAccel[i].y - gravityAccel[i].y;
        userAccel[i].z = totalAccel[i].z - gravityAccel[i].z;
    }
}

/**
 * dotProduct of userAccel and gravityAccel
 * to isolate movemnet in the direction of gravity
*/
void Filter::dotProduct(axes* userAccel, axes* gravityAccel,double *dp,int size)
{
    for(int i = 0; i < size; i++)
    {
        dp[i] = userAccel[i].x * gravityAccel[i].x + userAccel[i].y * gravityAccel[i].y + userAccel[i].z * gravityAccel[i].z;
    }
}