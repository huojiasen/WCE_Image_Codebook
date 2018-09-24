#pragma once
#ifndef DRAW
   //#define DRAW 1 
#endif
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>
#pragma comment(lib,"cv200.lib")
#pragma comment(lib,"cxcore200.lib")
#pragma comment(lib,"highgui200.lib")
using namespace std;
const int N = 24;//�ֽ�Ŀ���576
const int D = 10;//PCA���ά��
typedef struct point
{
	int x,y;
}_point;
typedef vector<double> Character;
typedef struct res
{
	_point s;
	int value;//�����ĳ̶�
	int w,h;//ͼ����㣬��ȣ��߶�
}_res;
class CSlient
{
private:
	vector<_res>   m_result;
	_point         m_start[N][N];
	IplImage      *m_InputImage;
	Character      m_Vec[N*N];
	double         m_Value[N][N];
	int            m_D;    //����ԭʼά��
	int            m_W;
	int            m_H;

public:
	CSlient();
	~CSlient();
private:
	void Divide();
	void CalSVD();
	double Distance(Character& t1,Character& t2);
	void NormalizeAndDraw();
public:
	void CalSalient(IplImage *in);
	const vector<_res>& getResult() const
	{
		return m_result;
	}
};
