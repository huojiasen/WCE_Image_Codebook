#include "CodeBookLoader.h"
CCodeBookLoader* CCodeBookLoader::instance = NULL;
void CCodeBookLoader::Load(string url)
{
	ifstream fin(url.c_str());
	string s; 
	for(int i=0;i<192;i++)
	{
		CodeMapNode cmn;
		cmn.value = new double[192];
		for(int j=0;j<=192;j++)
		{
			if(fin>>s)
			{
				if(j==0)
					cmn.name = s;
				else
					cmn.value[j-1] = atoi(s.c_str());;//×ª»¯Îªint
			}
			else
			{
				cout<<"IO error"<<endl;
				return;
			}
		}
		m_map.push_back(cmn);
	}
	fin.close();
}
