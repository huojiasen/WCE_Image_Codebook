#include "Gabor.h"
void CGabor::extract(IplImage *image)
{
	IplImage *hsv = cvCreateImage(cvGetSize(image),8,3);
	cvCvtColor(image,hsv,CV_RGB2HSV);
	IplImage *H = cvCreateImage(cvGetSize(image),8,1);
	IplImage *S = cvCreateImage(cvGetSize(image),8,1);
	IplImage *V = cvCreateImage(cvGetSize(image),8,1);
	cvCvtPixToPlane(hsv,H,S,V,0);

	int binsH = 8;
	int binsS = 4;
	float r[] = {0,255};
	float *ranges[] ={r};

	CvHistogram * histH = cvCreateHist(1,&binsH,CV_HIST_ARRAY,ranges,1);
	cvCalcHist(&H,histH,0,0);
	CvHistogram * histS = cvCreateHist(1,&binsS,CV_HIST_ARRAY,ranges,1);
	cvCalcHist(&S,histS,0,0);

	m_histogram = new double[d];
	for(int i=0;i<10;i++)
	{
		if(i<=6)
		{
			m_histogram[i] = cvQueryHistValue_1D(histH,i+1);
		}
		else
		{
			m_histogram[i] = cvQueryHistValue_1D(histS,i-6);
		}

	}
	//cout<<"the 10 bins:";
	//for(int i=0;i<10;i++)
	//	cout<<m_histogram[i]<<" ";
	//cout<<endl;
	cvReleaseImage(&image);
	cvReleaseImage(&hsv);
	cvReleaseImage(&H);
	cvReleaseImage(&S);
	cvReleaseImage(&V);

}
void CGabor::Double2String(double x,string &r)
{
	int y = static_cast<int>(x);
	r = "";
	do
	{
		int n = y%10;
		char a = n+48;
		r=a+r;
		y=y/10;
	}while(y!=0);
}
string CGabor::getStringRepresentation()
{
	string t;string s = "";
	s+="Gabor";
	s+=" ";
	s+="10";
	for(int i=0;i<10;i++)
	{
		s+=" ";
		Double2String(m_histogram[i],t);
		s+=t;
	}
	return s;
}
