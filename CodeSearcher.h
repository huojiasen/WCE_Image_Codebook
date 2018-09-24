#pragma once
#include "ImageSearcher.h"
#include "CodeBookLoader.h"
class CCodeSearcher:public iImageSearcher
{
private:
	static const int K = 15;
	set<CResult,MySortBig> m_Docs;
public:
	static CCodeBookLoader* m_loader;
public:
	CCodeSearcher()
	{
	}
	~CCodeSearcher()
	{
		//delete m_loader;
	}
public:
	CImageSearchHits* search(IplImage *image,IndexReader* reader);
};
