#include "ga.h"
//�ӽ�������ѡ�����������Ƶ�ĸ�ĸ
//ʵ�ֵ����л��ӽ����� 
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
			if (first % 2 == 0)//ѡ���ӽ��ĸ����
				gene_recom(one, mem);
			else
				one = mem;
		}
	}
}

//���棺ִ����ѡ����Ľ��档

void gene_recom(int one, int two)//�������麯��  
{
	int i;
	int point;
	if (nvare > 1)
	{
		if (nvare == 2)
			point = 1;
		else
			point = (rand() % (nvare - 1)) + 1;
		for (i = 0; i < point; i++)//ֻ�е�һ������������
			swap(&population[one].gene[i], &population[two].gene[i]);
	}
}

//Swap����������������2������

void swap(double *x, double *y)
{
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}


//Mutation function:���һ�±��졣ѡ�����ڱ���ı����ɱ���������֮������ֵ���档
//���캯�� 

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
