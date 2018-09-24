#include "Index.h"
HANDLE hMutex = CreateSemaphore(NULL,1,1,NULL);
void CIndex::readImage()
{
	_finddata_t file;long lf;
	string url = ImageDir+"*.jpg";//"../CBIR/"+ImageDir+"/*.jpg";
	if((lf=_findfirst(url.c_str(),&file))==-1)
		cout<<"no path!"<<endl;
	else
	{
		do 
		{
			m_ImageName.push_back(file.name);
			//cout<<"add file : "<<file.name<<endl;
		} while (_findnext(lf,&file)==0);
	}
	_findclose(lf);
}
CIndex* CIndex:: p =NULL;
void AnalyzeImage(int num)//并行程序设计 4个线程 资源互斥问题
{
	for(int i=0;i<CIndex::p->m_ImageName.size();i++)
	{
		if(i%4==num)
		{
			//iDocumentBuilder *b = CBuilderFactory::getColorBuilder();
			WaitForSingleObject(hMutex,INFINITE);
			iDocumentBuilder *b = CBuilderFactory::getFCTHBuilder();
			ReleaseSemaphore(hMutex,1,NULL);

			string name = CIndex::p->ImageDir+CIndex::p->m_ImageName[i]; 
			IplImage *src = cvLoadImage(name.c_str());
			Document *d = b->createDocument(src,CIndex::p->m_ImageName[i]);

			WaitForSingleObject(hMutex,INFINITE);
			CIndex::p->m_Docs.push_back(d);
			ReleaseSemaphore(hMutex,1,NULL);
			//cvReleaseImage(&src);
			CIndex::p->m_builder.push_back(b);
		}
	}
	return;
}
void CIndex::BuildIndex()
{
	readImage();
	if(m_ImageName.size()==0)
	{
		cout<<"there is no image"<<endl;
		return;
	}
	try
	{
		char *ndx=const_cast<char*>(IndexDir.c_str());//"D:/vc2008/ZFIM/CBIR/index/";//"../CBIR/index/";
		ndx[strlen(ndx)-1] = 0;
		lucene::analysis::WhitespaceAnalyzer an;
		IndexWriter* writer = _CLNEW IndexWriter(ndx,&an,true);
		writer->setMaxFieldLength(IndexWriter::DEFAULT_MAX_FIELD_LENGTH); 
		writer->setUseCompoundFile(true);
		//m_builder = CBuilderFactory::getColorBuilder();

		//AnalyzeImage(0);//顺序的算法

		HANDLE hThread[4];
		hThread[0]= CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AnalyzeImage,(LPVOID)0, 0, NULL); 
		hThread[1]= CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AnalyzeImage,(LPVOID)1, 0, NULL); 
		hThread[2]= CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AnalyzeImage,(LPVOID)2, 0, NULL);
		hThread[3]= CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AnalyzeImage,(LPVOID)3, 0, NULL);
		::WaitForMultipleObjects(4,hThread,TRUE,INFINITE);
		::CloseHandle(hThread[0]);
		::CloseHandle(hThread[1]);
		::CloseHandle(hThread[2]);
		::CloseHandle(hThread[3]);


		Document *doc;
		for(int i=0;i<m_Docs.size();i++)
		{
			doc = m_Docs[i];
			//==================print===========================
			//const TCHAR* ws = doc->get(_T("FCTH"));
			//char* us = new char[wcslen((const wchar_t *)ws)];
			//wcstombs(us,(const wchar_t *)ws,wcslen((const wchar_t *)ws));
			//string feature = us;
			//cout<<feature<<endl;
			//==============================================
			writer->addDocument(doc);
		}
		cout<<"document number:"<<m_Docs.size()<<endl;
		//writer->setUseCompoundFile(true);
		writer->optimize();
		writer->close();
		_CLLDELETE(writer);
	}
	catch(CLuceneError& err)
	{
		cout<<"Error:"<<err.what()<<endl;
	}
	catch(...)
	{
		cout<<"Unknown error"<<endl;
	}

	_lucene_shutdown(); //clears all static memory
}