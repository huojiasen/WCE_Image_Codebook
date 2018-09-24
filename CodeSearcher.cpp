#include "CodeSearcher.h"
#include "Distance.cpp"
#include "Slient.h"
#include "Fcth.h"
CCodeBookLoader* CCodeSearcher::m_loader = CCodeBookLoader::getInstance();
CImageSearchHits* CCodeSearcher::search(IplImage *image,IndexReader* reader)
{
	//=============提取查询图像的码本
	CSlient* slient = new CSlient();
	slient->CalSalient(image);
	CFcth* vd = new CFcth();
	vector<string> Words;
	vector<int>    Svalue;

	cout<<"parse code:";
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
		vd->extract(image);
		double *temp = new double[192];
		double* t = vd->getFeature();
		for(int i=0;i<192;i++)
		{
			temp[i]=t[i];
		}
		cvReleaseImage(&dst);

		double min=CDistance<double>::Euclidean(m_loader->getMap()[0].value,temp,192);
		string codeT = m_loader->getMap()[0].name;
		for(int i=1;i<m_loader->getMap().size();i++)
		{
			if(CDistance<double>::Euclidean(temp,m_loader->getMap()[i].value,192)<min)
			{
				min = CDistance<double>::Euclidean(temp,m_loader->getMap()[i].value,192);
				codeT = m_loader->getMap()[i].name;
			}
		}
		delete[] temp;
		Words.push_back(codeT);
		Svalue.push_back(r.value);
		cout<<codeT<<endl;
	}
	cout<<endl;
	delete slient;slient=NULL;
	delete vd;vd = NULL;
	//=================转化为term类型===============================
	vector<Term*> TermWords;
	for(int i=0;i<Words.size();i++)
	{
		const char *n = Words[i].c_str();
		TCHAR *nbuf = new TCHAR[2*Words[i].size()];
		STRCPY_AtoT(nbuf,n,2*Words[i].size());
		Term* t = new Term(_T("FCTH"),nbuf);
		TermWords.push_back(t);

		//====print=============================
		//const TCHAR* ws = t->toString();
		//char* us = new char[wcslen((const wchar_t *)ws)];
		//wcstombs(us,(const wchar_t *)ws,wcslen((const wchar_t *)ws));
		//string feature = us;
		//cout<<t->toString()<<endl;
		//======print============================
	}
	//======================测试term是否相等=========
	//Term* t1 = new Term(_T("FCTH"),_T("F41"));
	//string codeY = "F41";
	//const char *n = codeY.c_str();
	//TCHAR *nbuf = new TCHAR[2*codeY.size()];
	//STRCPY_AtoT(nbuf,n,2*codeY.size());
	//Term* t2 = new Term(_T("FCTH"),nbuf);
	//TermEnum* ss = reader->terms();
	//ss->next();
	//Term* t3 = ss->term();
	//if(t1->equals(t3))
	//	cout<<"they are equal"<<endl;
	//int n = reader->numDocs();//获取文档总数
	//int h = reader->docFreq(TermWords[1]);
	//TermDocs* termdocs = reader->termDocs(TermWords[1]);
	//int DocNo[10];int freq[10];
    //termdocs->read(DocNo,freq,10);
	//cout<<"total doc:"<<n<<endl;
	//cout<<"term1 in "<<h<<" docs"<<endl;
	//cout<<"doc with frequent: "<<DocNo[0]<<":"<<freq[0]<<endl;
	//=======================tf*idf排序法=========
	int numDoc = reader->numDocs();
	int *DocNo = new int[numDoc];
	int *No;
	int *TermFreq = new int[numDoc];
	double *score = new double[numDoc];
	for(int i=0;i<numDoc;i++)
	{
		DocNo[i]=-1;TermFreq[i]=-1;score[i]=0;
	}
	int DocFreq=0;double idf = 0;

	int mainsize =0;
	for(int i=0;i<TermWords.size();i++)
	{
		DocFreq = reader->docFreq(TermWords[i]);
		cout<<"doc freq: "<<DocFreq<<endl;
		idf = (double)numDoc/((double)DocFreq+1.0);
		idf=idf*Svalue[i];//idf以该词本的显著度作为分量
		for(int i=0;i<numDoc;i++)
		{
			DocNo[i]=-1;TermFreq[i]=-1;
		}
		TermDocs* termdocs = reader->termDocs(TermWords[i]);
		termdocs->read(DocNo,TermFreq,numDoc);
		//for(int i=0;i<numDoc;i++)
		//{
		//	if(DocNo[i]==-1)break;
		//	cout<<DocNo[i]<<" : "<<TermFreq[i]<<endl;
		//}
		
		
		if(i==0)
		{
			int j;
			for(j=0;j<numDoc;j++)
				if(DocNo[j]==-1)break;
			int size = j;
			No = new int[size];
			for(j=0;j<size;j++)
			{
				score[j]=TermFreq[j]*idf;
				No[j] = DocNo[j];
			}
			mainsize = size;
		}
		else
		{
			int j;
			for(j=0;j<numDoc;j++)
				if(DocNo[j]==-1)break;
			int size = j;
			for(j=0;j<size;j++)
			{
				for(int k=0;k<mainsize;k++)
				{
					if(DocNo[j]==No[k])
					{
						score[k]+=TermFreq[j]*idf;
					}
				}
			}
		}
	}
	for(int i=0;i<mainsize;i++)
	{
		cout<<No[i]<<" : "<<score[i]<<endl;
	}
	for(int i=0;i<mainsize;i++)
	{
		Document* d = reader->document(No[i]);
		CResult r(score[i],d);
		m_Docs.insert(r);
	}
	delete []DocNo;
	delete []No;
	delete []TermFreq;
	return new CImageSearchHits(m_Docs,1000);
}