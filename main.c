#include "ga.h"
//每一代都执行选择最佳成员，执行交叉和变异，然后评估结果种群，直到满足终止条件
void main() {
	int i;
	double temp;
	double temp1;
	if ((galog = fopen("data.txt", "w")) == NULL)
	{
		exit(1);
	}
	generation = 1;
	srand(time(NULL));
	fprintf(galog, "代数 最佳适应值 x	   y     平均值    总和值\n");
	printf("最佳结果\n");
	initialize();//初始化
	evaluate();//计算适应值
	keep_best();//寻找当代最优解
	temp = report();//记录,暂存上一代个体平均适应值   
	do
	{
		generation++;
		select();//筛选
		cross();//杂交
		mutate();//变异
		evaluate();//评价
		keep_best();
		elitist();
		temp1 = report();
		diff = fabs(temp - temp1);//求出两代平均适应值相差的绝对值
		temp = temp1;
	} while (generation < maxgen&&diff >= STOP);
	printf("\n最佳代数:%d\n", generation);
	for (i = 0; i < nvare; i++)
	{
		printf("X%d=%3.3f\n", i, population[peoplesize].gene[i]);
	}
	fclose(galog);
	printf("\n最佳适应值=%3.3f\n", population[peoplesize].fitness);
}

//随机值生成器：在范围内生成一个值
double randval(double low, double high)
{
	double val;
	val = ((double)(rand() % 10000) / 10000)*(high - low) + low;
	return val;
}
//报告函数：报告仿真进度并返回平均个体适应值
double report() {
	int i;
	double best_val;//种群内最优适应值
	double avg;//平均个体适应值 
	double sum_square;//种群内个体适应值平方和
	double sum;//种群适应值 
	sum = 0.0;
	sum_square = 0.0;
	for (i = 0; i < peoplesize; i++)
	{
		sum += population[i].fitness;
	}
	avg = sum / (double)peoplesize;
	best_val = population[peoplesize].fitness;
	fprintf(galog, "%6d  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f\n", generation, best_val, population[peoplesize].gene[0], population[peoplesize].gene[1], avg, sum);
	return avg;
}