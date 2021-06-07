#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>                
#define peoplesize 200  //�˿ڹ�ģ
#define maxgen 1000	    //������
#define nvare 2         //x��y����ֵ 
#define cro_pro 0.75	//������� 
#define mut_pro 0.15	//ͻ��Ŀ�����  
#define lbound 0     
#define ubound 12       //����ֵ���½�
#define STOP 0.001		//����ֹͣ����
int generation;         //��ǰһ��
int cur_best;           //��Ѹ���
double diff;			//��Ӧ�Ȳ�ֵ��ȷ���Ƿ�ֹͣ����
FILE *galog;            //����ļ�
struct genotype {
	double gene[nvare];     //�������
	double upper[nvare];    //�������ȡֵ��ȷ��
	double lower[nvare];    //�������ȡֵ��ȷ��
	double fitness;         //������Ӧֵ
	double rfitness;        //������Ӧֵռ��Ⱥ��Ӧֵ����
	double cfitness;        //������Ӧֵ���ۼӱ���
};//�����ͽṹ��
struct genotype population[peoplesize + 1]; //��ǰ��Ⱥ
struct genotype newpopulation[peoplesize + 1]; //����Ⱥ

void initialize();						  //��ʼ������
double randval(double, double);            //�������
double funtion(double x1, double x2);      //Ŀ�꺯��
void evaluate();						  //���ۺ���
void keep_best();					  //�������Ÿ���
void elitist();							  //��ǰ��Ⱥ���Ӵ���Ⱥ����ֵ�Ƚ�
void select();							  //ɸѡ����
void gene_recom(int one, int two);			  //�������麯��  
void cross();						  //�������麯��
void swap(double *, double *);            //��������
void mutate();							  //����ͻ�亯��
double report();						  //���ݼ�¼����