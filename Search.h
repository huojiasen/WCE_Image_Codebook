#pragma once
#include "ImageSearcherFactory.h"
class CSearch
{
private:
	CImageSearchHits *m_hits;
	IndexReader      *m_reader;
	string            IndexDir;
	iImageSearcher   *m_searcher;
public:
	CSearch(string t_indexDir="D:/vc2008/ZFIM/CBIR/index/")
		:m_hits(NULL),m_reader(NULL),IndexDir(t_indexDir),m_searcher(NULL)
	{

	}
	~CSearch()
	{
		delete m_hits;
		m_hits = NULL;
		//delete m_reader;
		m_reader = NULL;
		delete CCodeSearcher::m_loader;
		CCodeSearcher::m_loader = NULL;
		delete m_searcher;
		m_searcher = NULL;

	}
public:
	void searchForImage(string url = "a.jpg");
	void Test(string url);
	CImageSearchHits* getHits() const {return m_hits;}
};
