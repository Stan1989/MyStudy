// HebbianLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//////////////////////////////////////////////////////////////////////////
#define NUMCELL   5
int input[NUMCELL];
int output[NUMCELL];
double weight[NUMCELL][NUMCELL];
const double ration = 0.2;
//
void calculate_activations()
{
	for (int iOut = 0 ; iOut < NUMCELL; ++iOut)
	{
		double val = 0.0;
		for (int iIn = 0 ; iIn < NUMCELL ; ++iIn)
		{
			val += weight[iIn][iOut] * input[iIn]; 
		}
		if(val > 0.0) output[iOut] = 1;
		else
			output[iOut] = -1;
	}
}
void adjust_weights()
{
	for (int iIn = 0 ; iIn < NUMCELL ; ++iIn)
	{
		for (int iOut = 0 ; iOut < NUMCELL ; ++iOut)
		{
			weight[iIn][iOut] += ration * input[iIn] * output[iOut];
		}
	}
}




//
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

