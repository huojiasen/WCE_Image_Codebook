#pragma once
#include "ImageSearcher.h"
#include <set>
class CSimpleSearcher:public iImageSearcher
{
private:
	static const int K = 15;
	set<CResult,MySortSmall> m_Docs;
public:
	CSimpleSearcher()
	{
		m_Docs.clear();

	}
	~CSimpleSearcher()
	{
		//自动析构set
		cout<<"自动析构set"<<endl;
	}
public:
	const set<CResult,MySortSmall>& getDocs() const{return m_Docs;}
	CImageSearchHits* search(IplImage *image,IndexReader* reader);
	double getTopK(IndexReader* reader,iLireFeature *fs);
	double getDistance(Document* doc,iLireFeature *fs);
};
