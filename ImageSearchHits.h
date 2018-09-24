#pragma once
#include <vector>
#include "Result.h"
using namespace std;
class CImageSearchHits
{
private:
	//vector<CResult> m_results;
	vector<string> m_path;

public:
	CImageSearchHits(set<CResult,MySortSmall>& Docs,double maxDis)
	{
		for(set<CResult,MySortSmall>::iterator p=Docs.begin();p!=Docs.end();p++)
		{
			Document* doc = p->getDocument();
			const TCHAR* path = doc->get(_T("pathname"));
			char* path1 = new char[wcslen((const wchar_t *)path)];
			wcstombs(path1,(const wchar_t *)path,wcslen((const wchar_t *)path));
			string spath = path1;
			int i;
			for(i=0;i<spath.size();i++)
				if(spath[i]=='.')
					break;
			spath = spath.substr(0,i+4);
			m_path.push_back(spath);
			cout<<spath<<"the distance: "<<p->getDistance()<<endl;

		}
	}
	CImageSearchHits(set<CResult,MySortBig>& Docs,double maxDis)
	{
		for(set<CResult,MySortBig>::iterator p=Docs.begin();p!=Docs.end();p++)
		{
			Document* doc = p->getDocument();
			const TCHAR* path = doc->get(_T("pathname"));
			char* path1 = new char[wcslen((const wchar_t *)path)];
			wcstombs(path1,(const wchar_t *)path,wcslen((const wchar_t *)path));
			string spath = path1;
			int i;
			for(i=0;i<spath.size();i++)
				if(spath[i]=='.')
					break;
			spath = spath.substr(0,i+4);
			m_path.push_back(spath);
			cout<<spath<<" the distance: "<<p->getDistance()<<endl;

		}
	}
	CImageSearchHits()
	{
		m_path.clear();
	}
	virtual ~CImageSearchHits(void)
	{

	}
public:
	int length() const {return m_path.size();}
	string getPath(int i){return m_path[i];}
	string& operator[](int i) {return m_path[i];}
};
