#include "SimpleSearcher.h"
#include "Distance.cpp"
#include "Gabor.h"
CImageSearchHits* CSimpleSearcher::search(IplImage *image,IndexReader* reader)
{
	m_vd = new CGabor();
	m_vd->extract(image);
	double MaxDistance = getTopK(reader,m_vd);
	return new CImageSearchHits(m_Docs,MaxDistance);
}
double CSimpleSearcher::getTopK(IndexReader* reader,iLireFeature *fs)
{
	int numDocs = reader->numDocs();
	cout<<"the document num::"<<numDocs<<endl;
	double max = 0;
	IndexSearcher s(reader);
	Document *d;
	for(int i=0;i<numDocs;i++)
	{
		d = reader->document(i);// 无法读出所有文档
		double distance = getDistance(d,fs); 

		if(m_Docs.size()<=K)
		{
			if(distance>max) max = distance;
			CResult r(distance,d);
			m_Docs.insert(r);
		}
		else 
		{
			if(distance<max)
			{
				max = distance;
				CResult r(distance,d);
				//set<CResult,MySort>::iterator p = m_Docs.end();
				m_Docs.erase(m_Docs.begin());
				m_Docs.insert(r);
			}

		}
	}
	return 0;

}
double CSimpleSearcher::getDistance(Document* doc,iLireFeature *fs)
{
	double d = 0.0;
	double* p = ((CGabor*)fs)->getVector();//输入图像的特征向量

	double* q = new double[((CGabor*)fs)->getD()];//当前文档的特征向量
	const TCHAR* ws = doc->get(_T("featureGABOR"));
	char* us = new char[wcslen((const wchar_t *)ws)];
	wcstombs(us,(const wchar_t *)ws,wcslen((const wchar_t *)ws));
	string feature = us;
	//cout<<feature<<endl;
	//const TCHAR* path = doc->get(_T("pathname"));
	//char* path1 = new char[wcslen(path)];
	//wcstombs(path1,path,wcslen(path));
	//string spath = path1;
	//cout<<spath<<endl;

	for(int i=9,j=9,k=0;i<feature.size();i++)
	{
		if(feature[i]==' '||feature[i]==-85)
		{
			q[k]=atoi(feature.substr(j,i).c_str());
			k++;j=i+1;
		}
	}

	//for(int i=0;i<((CGabor*)fs)->getD();i++)
	//	cout<<q[i]<<" ";
	//cout<<endl;
	//for(int i=0;i<((CGabor*)fs)->getD();i++)
	//	cout<<p[i]<<" ";
	//cout<<endl;
	
	d = CDistance<double>::Euclidean(p,q,((CGabor*)fs)->getD());
	cout<<"each distance: "<<d<<endl;
	return d;

}

