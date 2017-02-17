/*
//Perceptrons Learning Algorithm
//xinxipan 2013-1-31
//cout<<"������\n"<<endl;
//cout<<"����Perceptrons Learning Algorithm����ȥhttp://blog.csdn.net/stan1989/article/details/8565499������һЩ�򵥵Ľ���"<<endl;
//cout<<"������������㷨��ⲻ��ȷ������ȥ������ַ�����ԣ��һᾡ�����ܽ��иĽ���"<<endl;
//cout<<"��������㷨���˹���������Ȥ����Ҳ�������Խ������ۡ�"<<endl;
//cout<<"ϣ���ҵĴ�������а���"<<endl;
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
		cout<<"right result��" <<slps[i].output<<"\t";
		cout<<"caculate result:" << compute(slps[i].inputs,weights)<<endl;
	}
	
	//
	char temp ;
	cin>>temp;
	return 0;
}
//////////////////////////////////////////////////////////////////////////