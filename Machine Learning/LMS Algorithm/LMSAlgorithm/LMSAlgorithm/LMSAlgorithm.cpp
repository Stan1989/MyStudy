/*
//LMS Algorithm
//xinxipan 2013-2-16
//cout<<"������\n"<<endl;
//cout<<"����LMS Algorithm����ȥ������һЩ�򵥵Ľ���"<<endl;
//cout<<"������������㷨��ⲻ��ȷ������ȥ������ַ�����ԣ��һᾡ�����ܽ��иĽ���"<<endl;
//cout<<"��������㷨���˹���������Ȥ����Ҳ�������Խ������ۡ�"<<endl;
//cout<<"ϣ���ҵĴ�������а���"<<endl;
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
	while(caculate_mse(testdata,weights) > 0.26)//��������ڸ���ֵ���㷨����
	{
		int iTest = rand()%nTests;//��ѵ�������У����ѡ��һ������
		double output = compute_output(testdata[iTest].inputs,weights);
		double err = testdata[iTest].output - output;
		//���������Ȩֵ
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
		cout<<"right result��" <<testdata[i].output<<"\t";
		cout<<"caculate result:" << classify_output(compute_output(testdata[i].inputs,weights))<<endl;
	}
	//
	char temp ;
	cin>>temp;
	return 0;
}

