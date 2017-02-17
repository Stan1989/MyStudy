/*
//Perceptrons Learning Algorithm
//xinxipan 2013-1-31
//cout<<"声明：\n"<<endl;
//cout<<"关于Perceptrons Learning Algorithm可以去http://blog.csdn.net/stan1989/article/details/8565499我做了一些简单的介绍"<<endl;
//cout<<"如果程序有误，算法理解不正确，可以去上述网址中留言，我会尽我所能进行改进。"<<endl;
//cout<<"如果对于算法和人工智能有兴趣读者也可以留言进行讨论。"<<endl;
//cout<<"希望我的代码对你有帮助"<<endl;
*/
#include "stdafx.h"
#include<iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////
//Perceptron Learning Algorithm(PLA)
//
const unsigned int nTests   = 4;
const unsigned int nInputs  = 2;
const double alpha = 0.2;
struct slp
{
	double inputs[nInputs];
	double output;
};

int compute(double * inputs,double * weights)
{
	double sum = 0.0;
	for (int i = 0 ; i < nInputs; ++i)
	{
		sum += weights[i]*inputs[i];
	}
	//bias
	sum += 1.0 * weights[nInputs];
	if(sum > 0.0)
		return 1;
	else
		return -1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	slp slps[nTests] = {
		{-1.0,-1.0,-1.0},
		{-1.0, 1.0, 1.0},
		{ 1.0,-1.0, 1.0},
		{ 1.0, 1.0, 1.0}
	};
	double weights[nInputs + 1] = {0.0};
	bool bLearningOK = false;
	while(!bLearningOK)
	{
		bLearningOK = true;
		for (int i = 0 ; i < nTests ; ++i)
		{
			int output = compute(slps[i].inputs,weights);
			if(output != (int)slps[i].output)
			{
				for (int w = 0 ; w < nInputs ; ++w)
				{
					weights[w] += alpha * slps[i].output * slps[i].inputs[w];
				}
				weights[nInputs] += alpha * slps[i].output ;
				bLearningOK = false;
			}
		}
	}
	for(int w = 0 ; w < nInputs + 1 ; ++w)
	{
		cout<<"weight"<<w<<":"<<weights[w]<<endl;
	}
	cout<<"\n";
	for (int i = 0 ;i < nTests ; ++i)
	{
		cout<<"right result：" <<slps[i].output<<"\t";
		cout<<"caculate result:" << compute(slps[i].inputs,weights)<<endl;
	}
	
	//
	char temp ;
	cin>>temp;
	return 0;
}
//////////////////////////////////////////////////////////////////////////