//////////////////////////////////////////////////////////////////////////
//single layer perceptrons(SLP)
bool slp_calculate_output(const double * inputs,const double * weights,int nInputs,int & output)
{
	if(NULL == inputs || NULL == weights)
		return false;
	double sum = 0.0;
	for (int i = 0 ; i < nInputs ; ++i)
	{
		sum += (weights[i] * inputs[i]);
	}
	//对以上的乘机和进行一定处理，这里我们对于sum大于0的，输出值赋值为1；其他的赋值为-1
	if(sum > 0.0)
		output = 1;
	else
		output = -1;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Multi-Layer perceptrons(MLP)
const unsigned int nInputs  = 4;
const unsigned int nOutputs = 3;
const unsigned int nHiddens = 4;
struct mlp
{
	double inputs[nInputs+1];//多一位是设置Bias的
	double outputs[nOutputs];
	double hiddens[nHiddens+1];//多一位是设置Bias的
	double weight_hiddens_2_inputs[nHiddens+1][nInputs+1];
	double weight_outputs_2_hiddens[nOutputs][nHiddens+1];
};
double sigmoid (double val)
{
	if(val > 0.0)
		return 1.0;
	else
		return -1.0;
}
bool mlp_calculate_outputs(mlp * pMlp)
{
	if(NULL == pMlp)
		return false;
	double sum = 0.0;
	for (int h = 0 ; h < nHiddens ; ++h)
	{
		double sum = 0.0;
		for (int i = 0 ; i < nInputs + 1 ; ++i)
		{
			sum += pMlp->weight_hiddens_2_inputs[h][i]*pMlp->inputs[i];
		}
		pMlp->hiddens[h] = sigmoid (sum);

	}
	for (int o = 0 ; o < nOutputs ; ++o)
	{
		double sum = 0.0;
		for (int h = 0 ; h < nHiddens + 1 ; ++h)
		{
			sum += pMlp->weight_outputs_2_hiddens[o][h]*pMlp->hiddens[h];
		}
		pMlp->outputs[o] = sigmoid (sum);
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////