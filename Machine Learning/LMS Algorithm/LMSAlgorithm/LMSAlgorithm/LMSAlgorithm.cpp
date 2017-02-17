/*
//LMS Algorithm
//xinxipan 2013-2-16
//cout<<"声明：\n"<<endl;
//cout<<"关于LMS Algorithm可以去我做了一些简单的介绍"<<endl;
//cout<<"如果程序有误，算法理解不正确，可以去上述网址中留言，我会尽我所能进行改进。"<<endl;
//cout<<"如果对于算法和人工智能有兴趣读者也可以留言进行讨论。"<<endl;
//cout<<"希望我的代码对你有帮助"<<endl;
*/
#include "stdafx.h"
#include <math.h>
#include<iostream>
using namespace std;

const unsigned int nTests   = 4;
const unsigned int nInputs  = 2;
const double rho = 0.005;

struct lms_testdata
{
	double inputs[nInputs];
	double output;
};

double compute_output(const double * inputs,double * weights)
{
	double sum = 0.0;
	for (int i = 0 ; i < nInputs; ++i)
	{
		sum += weights[i]*inputs[i];
	}
	//bias
	sum += weights[nInputs]*1.0;
	return sum;
}
double caculate_mse(const lms_testdata * testdata,double * weights)
{
	double sum = 0.0;
	for (int i = 0 ; i < nTests ; ++i)
	{
		sum += pow(testdata[i].output - compute_output(testdata[i].inputs,weights),2);
	}
	return sum/(double)nTests;
}
int classify_output(double output)
{
	if(output > 0.0)
		return 1;
	else
		return -1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	lms_testdata testdata[nTests] = {
		{-1.0,-1.0, -1.0},
		{-1.0, 1.0, -1.0},
		{ 1.0,-1.0, -1.0},
		{ 1.0, 1.0,  1.0}
	};
	double weights[nInputs + 1] = {0.0};
	while(caculate_mse(testdata,weights) > 0.26)//均方差大于给定值，算法继续
	{
		int iTest = rand()%nTests;//从训练数据中，随机选择一组数据
		double output = compute_output(testdata[iTest].inputs,weights);
		double err = testdata[iTest].output - output;
		//调整输入端权值
		for (int i = 0 ; i < nInputs ; ++i)
		{
			weights[i] = weights[i] + rho * err * testdata[iTest].inputs[i]; 
		}
		weights[nInputs] = weights[nInputs] + rho * err;
		cout<<"mse:"<<caculate_mse(testdata,weights)<<endl;
	}

	for(int w = 0 ; w < nInputs + 1 ; ++w)
	{
		cout<<"weight"<<w<<":"<<weights[w]<<endl;
	}
	cout<<"\n";
	for (int i = 0 ;i < nTests ; ++i)
	{
		cout<<"right result：" <<testdata[i].output<<"\t";
		cout<<"caculate result:" << classify_output(compute_output(testdata[i].inputs,weights))<<endl;
	}
	//
	char temp ;
	cin>>temp;
	return 0;
}

