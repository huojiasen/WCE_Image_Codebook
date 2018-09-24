#pragma once
#include "LireFeature.h"
#ifndef PRINT
   //#define PRINT 1 
#endif
template<class T>inline T MIN3(T a,T b,T c)
{
	if(a<=b&&a<=c)
		return a;
	else if(b<=a&&b<=c)
		return b;
	else return c;
}
class CFcth:public iLireFeature
{
private:
	int    m_meanRed,m_meanGreen,m_meanBlue;
	double m_block[4][4];
	double m_WaveletMatrix[3];
	double *m_10bin;
	double *m_24bin;
	double *m_192bin;
	static const int d10  = 10;
	static const int d24  = 24;
	static const int d192 = 192;
	//===============================================================================
	//      // => (m_meanRed,m_meanGreen,m_meanBlue)=>m_10bin=>m_24bin\\
	//     //                                                          \\
	// image                                                              =>m_192bin
	//     \\                                                          //  
	//      \\ =>                            m_block=>m_WaveletMatrix //
	//===============================================================================
public:
	CFcth();
	~CFcth();
public:
	void extract(IplImage *image);
	void extract(IplImage *image,int mode);
	void WaveletMatrix();
	void RGB2HSV(int r,int g,int b,int* hsv,int n);
	void Extract10Bin(double h,double s,double v);
    void Extract24Bin(double h,double s,double v);
	void Extract192Bin(double F1,double F2,double F3);
	void Quant();
	string getStringRepresentation();
	inline double* getFeature() const
	{
		return m_192bin;
	}
};
