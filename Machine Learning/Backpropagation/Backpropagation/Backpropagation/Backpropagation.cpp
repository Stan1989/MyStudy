// Backpropagation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<math.h>

#define NUM_INPUTS 4
#define NUM_HIDDENS 4
#define NUM_OUTPUTS 3
#define NUM_TESTS 10
#define ALPHA (double)0.2

double inputs[NUM_INPUTS];
double hiddens[NUM_HIDDENS];
double outputs[NUM_OUTPUTS];
double w_h_i[NUM_HIDDENS][NUM_INPUTS];
double w_o_h[NUM_OUTPUTS][NUM_HIDDENS];

struct TrainningSet
{
	double inputs[NUM_INPUTS];
	double outputs[NUM_OUTPUTS];
}TrainningSet;

TrainningSet tests[NUM_TESTS];

double sigmoid(double val)
{
	 return ( 1.0 / (1.0 + exp(-val)) );
}
double sigmoid_d(double val)
{
	return val*(1.0 - val);
}
//
void calculate_output()
{
	for (int i = 0 ; i < NUM_HIDDENS; ++i)
	{
		hiddens[i] = 0.0;
		for(int j = 0 ; j < NUM_HIDDENS ; ++j)
		{
			hiddens[i] += inputs[j] * w_h_i[i][j];
		}
		hiddens[i] = sigmoid(hiddens[i]);
	}

	for (int i = 0 ; i < NUM_OUTPUTS ; ++i)
	{
		outputs[i] = 0.0;
		for(int j = 0 ; j < NUM_HIDDENS ; ++j)
		{
			outputs[i] += hiddens[j] * w_o_h[i][j];
		}
		outputs[i] = sigmoid(outputs[i]);
	}
}

void backpropagate_error(int test)
{
	for (int i = 0 ; i < NUM_OUTPUTS ; ++i)
	{
		for (int j = 0 ; j < NUM_HIDDENS ; ++j)
		{
			w_o_h[i][j] = w_o_h[i][j] -ALPHA * (tests[test].outputs[i] - outputs[i]) * sigmoid_d(outputs[i]) * hiddens[j];
		}
	}
	//
	for (int i = 0 ; i < NUM_HIDDENS ; ++i)
	{
		for (int j = 0 ; j < NUM_INPUTS ; ++j)
		{
			w_h_i[i][j] = w_h_i[i][j] -ALPHA * (tests[test].hiddens[i] - hiddens[i]) * sigmoid_d(hiddens[i]) * inputs[j];
		}
	}
}

//

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

