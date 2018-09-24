#include "FCTHBuilder.h"
#include "Fcth.h"
#include "Slient.h"
int CFCTHBuilder::count = 0;
double CFCTHBuilder::distance(double* v1,double* v2,int d)
{
	double r = 0;
	for(int i=0;i<d;i++)
	{
		r+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return sqrt(r);
}
Document* CFCTHBuilder::createDocument(IplImage *image,string name)
{
	if(name.size()!=0)
	{
		const char *n = name.c_str();
		TCHAR *nbuf = new TCHAR[name.size()];
		STRCPY_AtoT(nbuf,n,name.size());
		StringBuffer ntr;
		ntr.append(nbuf);
		m_doc.add(*_CLNEW Field(_T("pathname"),ntr.getBuffer(), Field::STORE_YES | Field::INDEX_TOKENIZED));

	}
	m_vd = new CFcth();
	CSlient* slient = new CSlient();
	slient->CalSalient(image);
	StringBuffer str;
	cout<<"add code:";
	for(int j=0;j<slient->getResult().size();j++)
	{
		_res r = slient->getResult()[j];
		_point p = r.s;
		int w = r.w; int h = r.h;
		CvRect mask = cvRect(p.y,p.x,w,h);
		IplImage *dst = cvCreateImage(cvSize(w,h),8,3);
		cvSetImageROI(image,mask);
		cvCopy(image,dst);
		cvResetImageROI(image);
		m_vd->extract(image);
		double *temp = new double[192];
		double* t = m_vd->getFeature();
		for(int i=0;i<192;i++)
		{
			temp[i]=t[i];
		}
		cvReleaseImage(&dst);

		double min=distance(m_loader->getMap()[0].value,temp,192);
		string codeT = m_loader->getMap()[0].name;
		for(int i=1;i<m_loader->getMap().size();i++)
		{
			if(distance(temp,m_loader->getMap()[i].value,192)<min)
			{
				min = distance(temp,m_loader->getMap()[i].value,192);
				codeT = m_loader->getMap()[i].name;
			}
		}
		delete[] temp;
		cout<<codeT<<" ";
		codeT=codeT+" ";
		//======================================================
		string tempCode = codeT;
		int v = r.value;
		for(int k=0;k<v;k++)
			codeT=codeT+tempCode;
		//======================================================
		const char *s = codeT.c_str();
		TCHAR *tbuf = new TCHAR[codeT.size()];
		STRCPY_AtoT(tbuf,s,codeT.size());
		str.append(tbuf);
		//str.append(_T("F58 "));
	}
	delete slient;slient=NULL;
	
	m_doc.add(*_CLNEW Field(_T("FCTH"),str.getBuffer(), Field::STORE_YES | Field::INDEX_TOKENIZED));
	return &m_doc;
}