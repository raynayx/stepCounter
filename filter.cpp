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
        axes sum = {};
        for (int j = 0; j < window ; j++)
        {
            sum.x += X[i - j].x;
            sum.y += X[i - j].y;
            sum.z += X[i - j].z;
        }
        sum.x = (sum.x) / (float)window;
        sum.y = (sum.y) / (float)window;
        sum.z = (sum.z) / (float)window;
    }
}


void Filter::movingAverage(CB& X,CB& Y,int window)
{	
	if(first)
	{
        axes sum;
	for (int i = 0; i < window - 1; i++)
	{
		Y.push(sum);
	}
	for (int i = window - 1; i < X.size() ; i++)
	{
		axes sum;
		for (int j = 0; j < window ; j++)
		{
			sum.x += X[i - j].x;
			sum.y += X[i - j].y;
			sum.z += X[i - j].z;
		}
		sum.x = (sum.x) / (float)window;
		sum.y = (sum.y) / (float)window;
		sum.z = (sum.z) / (float)window;
		Y.push(sum);
	}
	first = false;
	return;
	}
	axes sum;
	for (int j = 1; j <= window ; j++)
	{
		sum.x += X[maxSize - j].x;
		sum.y += X[maxSize - j].y;
		sum.z += X[maxSize - j].z;
	}
	sum.x = (sum.x) / (float)window;
	sum.y = (sum.y) / (float)window;
	sum.z = (sum.z) / (float)window;
	Y.push(sum);

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

void Filter::getUserAccel(CB& totalAccel,CB& gravityAccel,CB& userAccel)
{
	axes temp;
    for(int i = 0; i < totalAccel.size(); i++)
    {
		temp.x = totalAccel[i].x - gravityAccel[i].x; 
		temp.y = totalAccel[i].y - gravityAccel[i].y;
		temp.z = totalAccel[i].z - gravityAccel[i].z;
		userAccel.push(temp);
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

void Filter::dotProduct(CB &userAccel,CB &gravityAccel,double *dp)
{
	for(int i=0; i < userAccel.size(); i++)
	{
		dp[i] = userAccel[i].x * gravityAccel[i].x + userAccel[i].y * gravityAccel[i].y + userAccel[i].z * gravityAccel[i].z;
	}
}

void Filter::movingAverage(double *X,double *Y, int size,int window)
{
	 for (int i = 0; i < window - 1; i++)
    {
        Y[i] = 0.0;

    }

    for (int i = window - 1; i < size ; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < window ; j++)
        {
            sum += X[i - j];
        }
        Y[i] = (sum) / window;
    }
}