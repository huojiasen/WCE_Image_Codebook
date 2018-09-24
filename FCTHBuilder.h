#pragma once
#include "DocumentBuilder.h"
#include "CodeBookLoader.h"
class CFCTHBuilder:public iDocumentBuilder
{
private:
	Document m_doc;
	CCodeBookLoader* m_loader;
	static int count;
public:
	CFCTHBuilder()
	{
		m_doc.clear();
		m_vd = NULL;
		m_loader = CCodeBookLoader::getInstance();
		count++;
	}
	~CFCTHBuilder()
	{
        delete m_vd;m_vd = NULL;
		count--;
		if(count==0)
		   delete m_loader;
	}
	Document* createDocument(IplImage *image,string name);
	double distance(double* v1,double* v2,int d);
};
