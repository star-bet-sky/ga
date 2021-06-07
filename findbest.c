#include "ga.h"
//Keep_the_best函数：此函数跟踪总体中的最佳成员。
//找出种群中的个体最优值并将其移动到最后 

void keep_best() {
	int mem;
	int i;
	cur_best = 0;
	for (mem = 0; mem < peoplesize; mem++)//找出最高适应值个体 
	{
		if (population[mem].fitness < population[cur_best].fitness)
		{
			cur_best = mem;
		}
	}
	//将最优个体复制至population[POSIZE] 
	if (population[cur_best].fitness <= population[peoplesize].fitness || population[peoplesize].fitness < 1)//防止出现种群基因退化 故保留历史最优个体 
	{
		population[peoplesize].fitness = population[cur_best].fitness;
		for (i = 0; i < nvare; i++)
			population[peoplesize].gene[i] = population[cur_best].gene[i];
	}
}

//Elitist函数：将上一代的最佳成员存储为数组中的最后一个成员。
//如果新populatin中的最佳个体优于上一种群的最佳个体，
//则从新种群中复制最佳种群；否则替换当前最差的个体，上一代最好的个体
//防止种群最优值退化 

void elitist() {
	int i;
	double best, worst;//适应值
	int best_mem, worst_mem;//序号 
	best_mem = worst_mem = 0;
	best = population[best_mem].fitness;//最高适应值初始化
	worst = population[worst_mem].fitness;//最低适应值初始化 
	for (i = 1; i < peoplesize; i++)//找出最高和最低适应值
	{
		if (population[i].fitness < best)
		{
			best = population[i].fitness;
			best_mem = i;
		}
		if (population[i].fitness > worst)
		{
			worst = population[i].fitness;
			worst_mem = i;
		}
	}
	if (best <= population[peoplesize].fitness)//赋值
	{
		for (i = 0; i < nvare; i++)
			population[peoplesize].gene[i] = population[best_mem].gene[i];
		population[peoplesize].fitness = population[best_mem].fitness;
	}
	else
	{
		for (i = 0; i < nvare; i++)
			population[worst_mem].gene[i] = population[peoplesize].gene[i];
		population[worst_mem].fitness = population[peoplesize].fitness;
	}
}

//筛选函数：采用精英模型的最大比例问题的标准比例选择-确保最佳成员幸存。
//筛选函数并产生子代

void select() {
	int mem, i, j;
	double sum = 0;
	double p;
	for (mem = 0; mem < peoplesize; mem++)//所有适应值求和
	{
		sum += population[mem].fitness;
	}
	for (mem = 0; mem < peoplesize; mem++)
	{
		population[mem].rfitness = population[mem].fitness / sum;
	}
	population[0].cfitness = population[0].rfitness;
	for (mem = 1; mem < peoplesize; mem++)
	{
		population[mem].cfitness = population[mem - 1].cfitness + population[mem].rfitness;
	}
	for (i = 0; i < peoplesize; i++)
	{
		p = rand() % 1000 / 1000.0;
		if (p < population[0].cfitness)
		{
			newpopulation[i] = population[0];
		}
		else
		{
			for (j = 0; j < peoplesize; j++)
				if (p >= population[j].cfitness&&p < population[j + 1].cfitness)
					newpopulation[i] = population[j + 1];
		}
	}
	for (i = 0; i < peoplesize; i++)//子代变父代
		population[i] = newpopulation[i];
}
