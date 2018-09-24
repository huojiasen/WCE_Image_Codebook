#include "Search.h"
#include "Gabor.h"
void CSearch::searchForImage(string url)
{
	try
	{
		char *ndx=const_cast<char*>(IndexDir.c_str());//"../CBIR/index/";
		ndx[strlen(ndx)-1] = 0;
		const char* index = ndx;
		m_reader = IndexReader::open(index);
		//m_searcher = CImageSearcherFactory::getSimpleSearcher();
		m_searcher = CImageSearcherFactory::getCodeSearcher();
		IplImage *src = cvLoadImage(url.c_str());
		m_hits = m_searcher->search(src,m_reader);

	}
	catch(CLuceneError& err)
	{
		printf("Error: %s\n", err.what());
	}
	catch(...)
	{
		printf("Unknown error\n");
	}

	m_reader->close();
	_CLLDELETE(m_reader);
	_lucene_shutdown(); 
	return;
}
void CSearch::Test(string url)
{
	try
	{
		char ndx[250]="../CBIR/index/";
		ndx[strlen(ndx)-1] = 0;
		const char* index = ndx;
		m_reader = IndexReader::open(index);
		m_searcher = CImageSearcherFactory::getSimpleSearcher();
		IplImage *src = cvLoadImage(url.c_str());
		//m_hits = m_searcher->search(src,m_reader);
		//Document* d = m_reader->document(0);
		iLireFeature* m_vd = new CGabor();
		m_vd->extract(src);
		//((CSimpleSearcher*)m_searcher)->getDistance(d,m_vd);
		((CSimpleSearcher*)m_searcher)->getTopK(m_reader,m_vd);
		cout<<"the size:"<<((CSimpleSearcher*)m_searcher)->getDocs().size();

	}
	catch(CLuceneError& err)
	{
		printf("Error: %s\n", err.what());
	}
	catch(...)
	{
		printf("Unknown error\n");
	}

	m_reader->close();
	_CLLDELETE(m_reader);
	_lucene_shutdown(); 
	return;

}
