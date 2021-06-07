#include "ga.h"
//Keep_the_best�������˺������������е���ѳ�Ա��
//�ҳ���Ⱥ�еĸ�������ֵ�������ƶ������ 

void keep_best() {
	int mem;
	int i;
	cur_best = 0;
	for (mem = 0; mem < peoplesize; mem++)//�ҳ������Ӧֵ���� 
	{
		if (population[mem].fitness < population[cur_best].fitness)
		{
			cur_best = mem;
		}
	}
	//�����Ÿ��帴����population[POSIZE] 
	if (population[cur_best].fitness <= population[peoplesize].fitness || population[peoplesize].fitness < 1)//��ֹ������Ⱥ�����˻� �ʱ�����ʷ���Ÿ��� 
	{
		population[peoplesize].fitness = population[cur_best].fitness;
		for (i = 0; i < nvare; i++)
			population[peoplesize].gene[i] = population[cur_best].gene[i];
	}
}

//Elitist����������һ������ѳ�Ա�洢Ϊ�����е����һ����Ա��
//�����populatin�е���Ѹ���������һ��Ⱥ����Ѹ��壬
//�������Ⱥ�и��������Ⱥ�������滻��ǰ���ĸ��壬��һ����õĸ���
//��ֹ��Ⱥ����ֵ�˻� 

void elitist() {
	int i;
	double best, worst;//��Ӧֵ
	int best_mem, worst_mem;//��� 
	best_mem = worst_mem = 0;
	best = population[best_mem].fitness;//�����Ӧֵ��ʼ��
	worst = population[worst_mem].fitness;//�����Ӧֵ��ʼ�� 
	for (i = 1; i < peoplesize; i++)//�ҳ���ߺ������Ӧֵ
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
	if (best <= population[peoplesize].fitness)//��ֵ
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

//ɸѡ���������þ�Ӣģ�͵�����������ı�׼����ѡ��-ȷ����ѳ�Ա�Ҵ档
//ɸѡ�����������Ӵ�

void select() {
	int mem, i, j;
	double sum = 0;
	double p;
	for (mem = 0; mem < peoplesize; mem++)//������Ӧֵ���
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
	for (i = 0; i < peoplesize; i++)//�Ӵ��丸��
		population[i] = newpopulation[i];
}
