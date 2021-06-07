#include "ga.h"
//初始化函数：初始化变量范围内的基因值。
//为每个个体数量初始化所有适应度值
void initialize() {
	int i, j;
	for (i = 0; i < nvare; i++)
	{
		for (j = 0; j < peoplesize + 1; j++)
		{
			if (!i)
			{
				population[j].fitness = 0;
				population[j].rfitness = 0;
				population[j].cfitness = 0;
			}
			population[j].lower[i] = lbound;
			population[j].upper[i] = ubound;
			population[j].gene[i] = randval(population[j].lower[i], population[j].upper[i]);
		}
	}
}
//目标函数 
double funtion(double x, double y) {
	double result1 = sqrt(x*x + y * y) + sqrt((x - 12)*(x - 12) + y * y) + sqrt((x - 8)*(x - 8) + (y - 6)*(y - 6));
	return result1;
}

//评价函数给出个体适应值

void evaluate() {
	int men;
	int i;
	double x[nvare];
	for (men = 0; men < peoplesize; men++)
	{
		for (i = 0; i < nvare; i++)
			x[i] = population[men].gene[i];
		population[men].fitness = funtion(x[0], x[1]);//将目标函数值作为适应值
	}
}
