#include "Slient.h"
#include <stdio.h>
#include <math.h>
void PrintMatrix(CvMat *Matrix,int Rows,int Cols)
{
	for(int i=0;i<Rows;i++)
	{
		for(int j=0;j<Cols;j++)
		{
			printf("%.2f ",cvmGet(Matrix,i,j));
		}
		printf("\n");
	}
}
bool EdgeLike(double i,double j)//过滤边界的影响，还需优化
{
	double x,y;
	x = y = static_cast<double>(N-1)/2.0;
	double r = sqrt((i-x)*(i-x)+(j-y)*(j-y));
	r = r-N/2;
	if(r>-N/12) return true;
	return false;
}
CSlient::CSlient():m_InputImage(NULL),m_D(0)
{
	m_result.clear();
}
CSlient::~CSlient()
{

}
void CSlient::Divide()
{
	IplImage *gray = cvCreateImage(cvGetSize(m_InputImage),8,1);
	cvCvtColor(m_InputImage,gray,CV_RGB2GRAY);
	if(gray->width%N==0&&gray->height%N==0)
	{
		int width = gray->width/N;
		int height = gray->height/N;
		m_W = width;
		m_H = height;
		m_D = width*height;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				 for(int ii=i*height;ii<i*height+height;ii++)
					 for(int jj=j*width;jj<j*width+width;jj++)
					 {
						 double a = cvGetReal2D(gray,ii,jj);
						 m_Vec[i*N+j].push_back(a);
					 }
				 /*if(i==0&&j==0)
				 {
					 for(int ii=0;ii<m_Vec[0].size();ii++)
					 {

						 cout<<m_Vec[i*N+j][ii]<<" ";
						 if(ii%width==(width-1))
							 cout<<endl;
					 }
				 }*/
			}
	}
	cvReleaseImage(&gray);
}
void CSlient::CalSVD()
{
	int m = N*N;
	int n = m_D;
	CvMat *Matrix=cvCreateMat(m,n,CV_64FC1);
	CvMat *U=cvCreateMat(m,m,CV_64FC1);
	CvMat *W=cvCreateMat(m,n,CV_64FC1);
	CvMat *V=cvCreateMat(n,n,CV_64FC1);
	CvMat *ResultMatrix=cvCreateMat(m,n,CV_64FC1);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			cvmSet(Matrix,i,j,m_Vec[i][j]);
		}
	cvSVD(Matrix,W,U,V);
	//PrintMatrix(W,W->rows,W->cols);
	for(int i=D;i<m;i++)
		for(int j=0;j<n;j++)
		{
			cvmSet(W,i,j,0);//规约维度设置为0
		}
	cvmMul(U,W,ResultMatrix);
   // PrintMatrix(ResultMatrix,ResultMatrix->rows,ResultMatrix->cols);

	for(int i=0;i<m;i++)
		m_Vec[i].clear();
	for(int i=0;i<m;i++)
		for(int j=0;j<D;j++)
			m_Vec[i].push_back(cvmGet(ResultMatrix,i,j));
	//for(int i=0;i<m;i++)
	//{
	//	for(int j=0;j<m_Vec[i].size();j++)
	//		cout<<m_Vec[i][j]<<" ";
	//	cout<<endl;
	//}
	cvReleaseMat(&Matrix );
	cvReleaseMat(&U);
	cvReleaseMat(&W);
	cvReleaseMat(&V);
	cvReleaseMat(&ResultMatrix);

}
double CSlient::Distance(Character& t1,Character& t2)
{
	double dist=-1;
	if(t1.size()==t2.size())
	{
		dist = 0;
		for(int i=0;i<t1.size();i++)
		{
			dist+=(t1[i]-t2[i])*(t1[i]-t2[i]);
		}
		dist = sqrt(dist);
	}

	return dist;
}
void CSlient::NormalizeAndDraw()
{
	double max =0 ;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			if(EdgeLike(i,j))m_Value[i][j]=0;
			if(m_Value[i][j]>max)max = m_Value[i][j];
		}
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			m_Value[i][j]=m_Value[i][j]*255.0/max;
		}
	//for(int i=0;i<N;i++)
	//{
	//	for(int j=0;j<N;j++)
	//		cout<<(int)m_Value[i][j]<<" ";
	//	cout<<endl;
	//}
#ifdef DRAW
		IplImage *g = cvCreateImage(cvGetSize(m_InputImage),8,3);
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				int arr[1];arr[0] = 4;  
				CvPoint ** pt = new CvPoint*[1];  
				pt[0] = new CvPoint[4];  
				pt[0][0] = cvPoint(j*20,i*20);  
				pt[0][1] = cvPoint(j*20,i*20+20);  
				pt[0][2] = cvPoint(j*20+20,i*20+20);  
				pt[0][3] = cvPoint(j*20+20,i*20); 
				if(EdgeLike(i,j))m_Value[i][j]=0;
				cvFillPoly(g,pt,arr,1,CV_RGB(0,(int)m_Value[i][j],0)); 
			}
			cvNamedWindow("gray",1);
			cvShowImage("gray",g);
#endif
	
}
void CSlient::CalSalient(IplImage *in)
{
	m_InputImage = in;
	Divide();
	CalSVD();
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			double v = 0;
			for(int ii=-1;ii<=1;ii++)
				for(int jj=-1;jj<=1;jj++)
				{
					int ri = i+ii;int ci = j+jj;
					if(ri>=0&&ri<N&&ci>=0&&ci<N)
						v+=Distance(m_Vec[i*N+j],m_Vec[ri*N+ci]);
				}
			m_Value[i][j]=v;
		}
	NormalizeAndDraw();
	m_result.clear();
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			if(!EdgeLike(i,j))
			{
				int num=0;
				if(m_Value[i][j]>=50)
				{
					for(int ii=-2;ii<=2;ii++)
						for(int jj=-2;jj<=2;jj++)
						{
							int ri = i+ii;int ci = j+jj;
							if(m_Value[ri][ci]<m_Value[i][j])num++;
						}
					if(num==24)
					{
						_res r;
						r.s.x = i*m_H;r.s.y = j*m_W;
						r.h = m_H;r.w = m_W;
						r.value = m_Value[i][j];
						m_result.push_back(r);
					}
				}
				
			}
		}
#ifdef DRAW
		for(int i=0;i<m_result.size();i++)
		{
			cout<<"("<<m_result[i].s.x<<","<<m_result[i].s.y<<")";
			cout<<m_result[i].value<<endl;
		}


		for(int i=0;i<m_result.size();i++)
		{
			int arr[1];arr[0] = 4;  
			CvPoint ** pt = new CvPoint*[1];  
			pt[0] = new CvPoint[4];  
			pt[0][0] = cvPoint(m_result[i].s.y,m_result[i].s.x);  
			pt[0][1] = cvPoint(m_result[i].s.y,m_result[i].s.x+m_result[i].h);  
			pt[0][2] = cvPoint(m_result[i].s.y+m_result[i].w,m_result[i].s.x+m_result[i].h);  
			pt[0][3] = cvPoint(m_result[i].s.y+m_result[i].w,m_result[i].s.x); 
			cvPolyLine(m_InputImage,pt,arr,1,1,CV_RGB(250,0,0)); 

		}
		cvNamedWindow("src",1);
		cvShowImage("src",m_InputImage);
		cvWaitKey(0);
		cvReleaseImage(&m_InputImage);
		cvDestroyWindow("src");
#endif
		//cvReleaseImage(&m_InputImage);
}