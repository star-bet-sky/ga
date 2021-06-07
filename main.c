#include "ga.h"
//ÿһ����ִ��ѡ����ѳ�Ա��ִ�н���ͱ��죬Ȼ�����������Ⱥ��ֱ��������ֹ����
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
	fprintf(galog, "���� �����Ӧֵ x	   y     ƽ��ֵ    �ܺ�ֵ\n");
	printf("��ѽ��\n");
	initialize();//��ʼ��
	evaluate();//������Ӧֵ
	keep_best();//Ѱ�ҵ������Ž�
	temp = report();//��¼,�ݴ���һ������ƽ����Ӧֵ   
	do
	{
		generation++;
		select();//ɸѡ
		cross();//�ӽ�
		mutate();//����
		evaluate();//����
		keep_best();
		elitist();
		temp1 = report();
		diff = fabs(temp - temp1);//�������ƽ����Ӧֵ���ľ���ֵ
		temp = temp1;
	} while (generation < maxgen&&diff >= STOP);
	printf("\n��Ѵ���:%d\n", generation);
	for (i = 0; i < nvare; i++)
	{
		printf("X%d=%3.3f\n", i, population[peoplesize].gene[i]);
	}
	fclose(galog);
	printf("\n�����Ӧֵ=%3.3f\n", population[peoplesize].fitness);
}

//���ֵ���������ڷ�Χ������һ��ֵ
double randval(double low, double high)
{
	double val;
	val = ((double)(rand() % 10000) / 10000)*(high - low) + low;
	return val;
}
//���溯�������������Ȳ�����ƽ��������Ӧֵ
double report() {
	int i;
	double best_val;//��Ⱥ��������Ӧֵ
	double avg;//ƽ��������Ӧֵ 
	double sum_square;//��Ⱥ�ڸ�����Ӧֵƽ����
	double sum;//��Ⱥ��Ӧֵ 
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