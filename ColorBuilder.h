#pragma once
#include "DocumentBuilder.h"
class CColorBuilder:public iDocumentBuilder
{
private:
	Document m_doc;

public:
	CColorBuilder()
	{
		m_doc.clear();
		m_vd = NULL;
	}
	virtual ~CColorBuilder()
	{
        delete m_vd;m_vd = NULL;
	}
	Document* createDocument(IplImage *image,string name);
};
