#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>                
#define peoplesize 200  //人口规模
#define maxgen 1000	    //最大代数
#define nvare 2         //x和y两个值 
#define cro_pro 0.75	//交叉概率 
#define mut_pro 0.15	//突变的可能性  
#define lbound 0     
#define ubound 12       //基因值上下界
#define STOP 0.001		//迭代停止变量
int generation;         //当前一代
int cur_best;           //最佳个体
double diff;			//适应度差值，确定是否停止迭代
FILE *galog;            //输出文件
struct genotype {
	double gene[nvare];     //基因变量
	double upper[nvare];    //基因变量取值上确界
	double lower[nvare];    //基因变量取值下确界
	double fitness;         //个体适应值
	double rfitness;        //个体适应值占种群适应值比例
	double cfitness;        //个体适应值的累加比例
};//基因型结构体
struct genotype population[peoplesize + 1]; //当前种群
struct genotype newpopulation[peoplesize + 1]; //子种群

void initialize();						  //初始化函数
double randval(double, double);            //随机函数
double funtion(double x1, double x2);      //目标函数
void evaluate();						  //评价函数
void keep_best();					  //保留最优个体
void elitist();							  //当前种群与子代种群最优值比较
void select();							  //筛选函数
void gene_recom(int one, int two);			  //基因重组函数  
void cross();						  //基因重组函数
void swap(double *, double *);            //交换函数
void mutate();							  //基因突变函数
double report();						  //数据记录函数