// PNN_Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<math.h>

#define CLASSNUM     5
#define EXAMPLENUM  10
#define DIMENSIONALITY 2

const double sigma = 0.02233;

double example[DIMENSIONALITY];
struct Example
{
	double f[DIMENSIONALITY];
};
struct DataSet
{
	Example example[EXAMPLENUM];
};
DataSet dataset[CLASSNUM];

int pnn_classify()
{
	double output[CLASSNUM];
	for(int c = 0 ; c < CLASSNUM ; ++c)
	{
		output[c] = 0.0;
		for(int e = 0 ; e < EXAMPLENUM ; ++e)
		{
			double h = 0.0;
			for(int d = 0 ; d < DIMENSIONALITY ; ++d)
			{
				h += example[d] * dataset[c].example[e].f[d];
			}
			output[c] = exp((h-1.0)/pow(sigma,2));
		}
		output[c] = output[c] / (double)EXAMPLENUM;
	}
	//winner take all
	double maxActivation = 0.0;
	int iCMax = 0;
	for (int c = 0 ; c < CLASSNUM ; ++c)
	{
		if(maxActivation < output[c])
		{
			iCMax = c;
			maxActivation = output[c];
		}
	}
	return iCMax;
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

