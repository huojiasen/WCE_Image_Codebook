#pragma once
#include "LireFeature.h"

class CGabor:public iLireFeature
{
private:
	static const int d = 10;
	double *m_histogram;
public:
	CGabor():m_histogram(NULL)
	{

	}
	virtual ~CGabor()
	{
		delete []m_histogram;
		m_histogram = NULL;
	}
	void extract(IplImage *image);
	string getStringRepresentation();
	void Double2String(double x,string &r);
	double* getVector() const{return m_histogram;}
	int getD() const {return d;}
	inline double* getFeature() const
	{
		return m_histogram;
	}
};
