#pragma once
#include "LuceneHeader.h"
#include <set>
class CResult
{
private:
     double m_distance;
	 Document* m_document;
public:
	CResult(double t,Document *d):m_distance(t),m_document(d)
	{

	}
	~CResult()
	{
		//cout<<"Îö¹¹Result"<<endl;
		//delete m_document;
		m_document = NULL;
	}
public:
	double getDistance() const{return m_distance;}
	void setDistance(double t){m_distance = t;}
	Document* getDocument() const{return m_document;}
};
class MySortSmall:public greater<CResult>
{
public:
	bool operator()(CResult b1,CResult b2) const
	{
		return b1.getDistance()<b2.getDistance();
	}

};
class MySortBig:public greater<CResult>
{
public:
	bool operator()(CResult b1,CResult b2) const
	{
		return b1.getDistance()>b2.getDistance();
	}

};

