#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;
#define C 192//�������192�����
#define D 192//������ά��
class CFCM
{
private:
    int     numpattern;   //������
    int     dimension;    //ÿ���������ά��
    int     cata;         //Ҫ����������
    int     maxcycle;     //���ĵ�������
    double  m;         //����m
    double  limit;     //�����;

	double* m_pattern;  //��������
	double* m_matrix;   //��ϵ����
	double* m_center;   //��������
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
