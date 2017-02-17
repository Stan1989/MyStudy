#Machine Learning---感知器学习算法
##引言
这里开始介绍神经网络方面的知识（Neural Networks）。首先我们会介绍几个监督式学习的算法，随后便是非监督式的学习。
##第1章 感知器学习算法基本介绍
###1.1. 神经网络
就像进化计算，神经网络又是一个类似的概念。神经网络由一个或者多个神经元组成。而一个神经元包括输入、输出和“内部处理器”。神经元从输入端接受信息，通过“内部处理器”将这些信息进行一定的处理，最后通过输出端输出。
###1.2. 感知器
感知器（Perceptron），是神经网络中的一个概念，在1950s由Frank Rosenblatt第一次引入。
###1.3. 单层感知器
单层感知器（Single Layer Perceptron）是最简单的神经网络。它包含输入层和输出层，而输入层和输出层是直接相连的。

<center>![](http://stan-zhao.com/wp-content/uploads/2017/02/th.jpg)</center>
<center>图1</center>

图1便是一个单层感知器，很简单一个结构，输入层和输出层直接相连。
接下来介绍一下如何计算输出端。

![](http://stan-zhao.com/wp-content/uploads/2017/02/formula1-1.png)

利用公式1计算输出层，这个公式也是很好理解。首先计算输入层中，每一个输入端和其上的权值相乘，然后将这些乘机相加得到乘机和。对于这个乘机和做如下处理，如果乘机和大于临界值（一般是0），输入端就取1；如果小于临界值，就取-1。
以下就给出一段单层感知器的代码。
<pre>
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
//这里我们对乘机和的处理：如果大于0，则输出值为1；其他情况，输出值为-1
	if(sum > 0.0)
		output = 1;
	else
		output = -1;
}
</pre>

单层感知器其简单的特性，可以提供快速的计算。它能够实现逻辑计算中的NOT、OR、AND等简单计算。
但是对于稍微复杂的异或就无能无力。下面介绍的多层感知器，就能解决这个问题。
###1.4. 多层感知器
多层感知器（Multi-Layer Perceptrons），包含多层计算。
相对于单层感知器，输出端从一个变到了多个；输入端和输出端之间也不光只有一层，现在又两层:输出层和隐藏层。
<center>![](http://stan-zhao.com/wp-content/uploads/2017/02/artificial_neural_network.svg_.png)</center>
<center>图2</center>

图2.2就是一个多层感知器。
对于多层感知器的计算也是比较简单易懂的。首先利用公式1计算每一个。
看一下它代码，就能明白它的工作原理。
<pre>
//Multi-Layer perceptrons(MLP)
const unsigned int nInputs  = 4;
const unsigned int nOutputs = 3;
const unsigned int nHiddens = 4;
struct mlp
{
	double inputs[nInputs+1];//多一个，存放的bias，一般存放入1
	double outputs[nOutputs];
	double hiddens[nHiddens+1]; //多一个，存放的bias，一般存放入1
	double weight_hiddens_2_inputs[nHiddens+1][nInputs+1];
	double weight_outputs_2_hiddens[nOutputs][nHiddens+1];
};
//这里我们对乘机和的处理：如果大于0，则输出值为1；其他情况，输出值为-1
double sigmoid (double val)
{
	if(val > 0.0)
		return 1.0;
	else
		return -1.0;
}
//计算输出端
bool mlp_calculate_outputs(mlp * pMlp)
{
	if(NULL == pMlp)
		return false;
	double sum = 0.0;
    //首先计算隐藏层中的每一个结点的值
	for (int h = 0 ; h < nHiddens ; ++h)
	{
		double sum = 0.0;
		for (int i = 0 ; i < nInputs + 1 ; ++i)
		{
			sum += pMlp->weight_hiddens_2_inputs[h][i]*pMlp->inputs[i];
		}
	    pMlp->hiddens[h] = sigmoid (sum);

	}
     //利用隐藏层作为“输入层”，计算输出层
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

</pre>

##第2章 感知器学习算法
###2.1. 感知器学习
其实感知器学习算法，就是利用第一节介绍的单层感知器。首先利用给的正确数据，计算得到输出值，将输出值和正确的值相比，由此来调整每一个输出端上的权值。

![](http://stan-zhao.com/wp-content/uploads/2017/02/formula2-1.png)

公式2便是用来调整权值，首先α是一个“学习参数”，一般我将它设置成小于1的正数。T便是训练数据中的正确结果，![](http://stan-zhao.com/wp-content/uploads/2017/02/input_i.png)便是第i个输入端的输入值，![](http://stan-zhao.com/wp-content/uploads/2017/02/weight_i.png)便是第i个输入端上面的权值。

###2.2. 代码
对于其介绍，我还是附上代码。
<pre>
//Perceptron Learning Algorithm(PLA)
const unsigned int nTests   = 4; //训练数据的数量
const unsigned int nInputs  = 2; //输入端的数量
const double alpha = 0.2;        //学习参数
struct slp
{
	double inputs[nInputs];
	double output;
}; //单层感知器
//计算输出值
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
//
int _tmain(int argc, _TCHAR* argv[])
{
//正确的训练数据
	slp slps[nTests] = {
		{-1.0,-1.0,-1.0},
		{-1.0, 1.0, 1.0},
		{ 1.0,-1.0, 1.0},
		{ 1.0, 1.0, 1.0}
	};
	double weights[nInputs + 1] = {0.0};
	bool bLearningOK = false;
  //感知器学习算法
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
		cout<<"weight"<<w<<":"<<weights[w] <<endl;
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
</pre>

###2.3. 效果图
下面附上运行效果图
<center>![](http://stan-zhao.com/wp-content/uploads/2017/02/result.png)</center>
<center>图3</center>

##第3章 总结
感知器学习算法，算是神经网络中的最简单的学习算法。但是通过这个进入学习神经网络学习算法，是个不错的选择。
感知器学习算法，只要是利用了单层感知器。这篇文章中，我们还了解到了另一种感知器：多层感知器。多层感知器主要是用于方向传播学习算法中，这个我后面的文章中会进行介绍。
由于笔者不是专门研究人工智能方面，所以在写这些文章的时候，肯定会有一些错误，也请谅解，上面介绍中有什么错误或者不当地方，敬请指出，不甚欢迎。

如果有兴趣的可以留言，一起交流一下算法学习的心得。
声明：本文章是笔者整理资料所得原创文章，如转载需注明出处，谢谢。
