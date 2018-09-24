#pragma once
#include "LireFeature.h"
#include "LuceneHeader.h"
#include "ImageSearchHits.h"
class iImageSearcher
{
protected:
	iLireFeature* m_vd;
public:
	virtual ~iImageSearcher(){};
	virtual CImageSearchHits* search(IplImage *image,IndexReader* reader)=0;
};