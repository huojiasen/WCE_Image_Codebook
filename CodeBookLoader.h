#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
struct CodeMapNode
{
	string name;
	double *value;
};

const string g_url = "codebook";
class CCodeBookLoader
{ 
private:
	typedef vector<CodeMapNode> CodeMap;
	CodeMap  m_map;
	static CCodeBookLoader *instance;
private:
	CCodeBookLoader()
	{
		m_map.clear();
		Load(g_url);
	}
	void Load(string url);
public:
	static CCodeBookLoader* getInstance()
	{
		if(instance == NULL)
			instance = new CCodeBookLoader();
		return instance;
	}
	~CCodeBookLoader()
	{
		for(int i=0;i<m_map.size();i++)
		{
			delete[] m_map[i].value;
			m_map[i].value = NULL;
		}

	}
	const CodeMap& getMap() const
	{
		return m_map;
	}
};
