#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;
#define C 192//聚类产生192个类别
#define D 192//样本的维度
class CFCM
{
private:
    int     numpattern;   //样本数
    int     dimension;    //每个样本点的维数
    int     cata;         //要聚类的类别数
    int     maxcycle;     //最大的迭代次数
    double  m;         //参数m
    double  limit;     //误差限;

	double* m_pattern;  //样本数据
	double* m_matrix;   //关系矩阵
	double* m_center;   //聚类中心
public:
	CFCM(int n, int d, int c, int max, double m, double l)
		:numpattern(n),dimension(d),cata(c),maxcycle(max),m(m),limit(l)
	{
		m_pattern = new double[numpattern*dimension];
		m_matrix = new double[numpattern*cata];
		m_center = new double[cata*dimension];
	}
	CFCM(int n)
	{
		CFCM(n,D,C,10,2,0.01);
	}
	~CFCM()
	{
       delete []m_pattern;m_pattern = NULL;
	   delete []m_matrix;m_matrix = NULL;
	   delete []m_center;m_center = NULL;
	}
public:
	void   runFCM();
	void   Import(const vector<double*>& t);
	void   Export(string filename = "codebook");
private:
	double distance(double* v1,double* v2,int dimen);
	double objectfun();
	void   dump();
};
