#pragma once
#include "BuilderFactory.h"
#include <windows.h>
class CIndex
{
public:
	friend void AnalyzeImage(int num);
	static CIndex *p;
private:
	vector<string> m_ImageName;
	vector<Document *> m_Docs;
	vector<iDocumentBuilder*> m_builder;
	string IndexDir;
	string ImageDir;
	//string Url;
public:
	CIndex(string t_indexDir="D:/vc2008/ZFIM/CBIR/index/",string t_ImageDir="D:/vc2008/ZFIM/CBIR/image/"):
	  IndexDir(t_indexDir),ImageDir(t_ImageDir),m_builder(NULL)
    {
		m_ImageName.clear();
	    m_Docs.clear();
	    m_builder.clear();
	}
	virtual ~CIndex()
	{
		//for(int i=0;i<m_Docs.size();i++)
		//{
		//	delete m_Docs[i];
		//	m_Docs[i] = NULL;
		//}//lucene×Ô¶¯ÊÍ·Å
		m_Docs.clear();
		for(int i=0;i<m_builder.size();i++)
		{
			delete m_builder[i];
			m_builder[i] = NULL;
		}

		m_builder.clear();
	}
public:
	void readImage();
	void BuildIndex();
	const string& getImageDir() const{return ImageDir;}
	const string& getIndexDir() const{return IndexDir;}
	void setImageDir(const string& t){ImageDir = t;}
	void setIndexDir(const string& t){IndexDir = t;}

};
