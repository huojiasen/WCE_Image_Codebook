#include "Slient.h"
#include "Fcth.h"
#include "CodeBook.h"
#include "Index.h"
#include "Search.h"
inline void slicentG()
{
	IplImage* image = cvLoadImage("416.jpg");
	CSlient* slient = new CSlient();
	slient->CalSalient(image);
	delete slient;
}
inline void buildG()
{
	CCodeBook *cb = new CCodeBook("D:/vc2008/ZFIM/CBIR/image/");
	cb->ReleaseCodeBook();
	delete cb;
}
inline void indexG()
{
	CIndex* i = new CIndex();
	CIndex::p = i;
	i->setImageDir("D:/vc2008/ZFIM/CBIR/image/");
	i->setIndexDir("D:/vc2008/ZFIM/CBIR/index/");
	i->BuildIndex();
	delete i;
	CIndex::p = NULL;
}
inline void searchG()
{
	CSearch *s = new CSearch(); 
	s->searchForImage("147.jpg");
	delete s;
}
int main()
{
	//buildG();
	//indexG();
	searchG();
	//slicentG();
	int mmm;
	cin>>mmm;
	return 0;  
}
