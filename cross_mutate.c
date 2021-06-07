#include "ga.h"
//杂交函数：选择两个参与分频的父母
//实现单点切换杂交函数 
void cross() {
	int mem, one;
	int first = 0;
	double x;
	for (mem = 0; mem < peoplesize; ++mem)
	{
		x = rand() % 1000 / 1000.0;
		if (x < cro_pro)
		{
			++first;
			if (first % 2 == 0)//选择杂交的个体对
				gene_recom(one, mem);
			else
				one = mem;
		}
	}
}

//交叉：执行所选父项的交叉。

void gene_recom(int one, int two)//基因重组函数  
{
	int i;
	int point;
	if (nvare > 1)
	{
		if (nvare == 2)
			point = 1;
		else
			point = (rand() % (nvare - 1)) + 1;
		for (i = 0; i < point; i++)//只有第一个基因发生重组
			swap(&population[one].gene[i], &population[two].gene[i]);
	}
}

//Swap：交换函数，交换2个变量

void swap(double *x, double *y)
{
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}


//Mutation function:随机一致变异。选择用于变异的变量由变量上下限之间的随机值代替。
//变异函数 

void mutate()
{
	int i, j;
	double bound, hbound;
	double x;
	for (i = 0; i < peoplesize; i++)
		for (j = 0; j < nvare; j++)
		{
			x = rand() % 1000 / 1000.0;
			if (x < mut_pro)
			{
				bound = population[i].lower[j];
				hbound = population[i].upper[j];
				population[i].gene[j] = randval(bound, hbound);
			}
		}
}
