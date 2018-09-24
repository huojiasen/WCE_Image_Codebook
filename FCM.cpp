#include "FCM.h"
void CFCM::dump()
{
	static int n = 1;
	cout<<"matrix:"<<n<<endl;
	for(int i=0;i<numpattern;i++)
	{
		for(int j=0;j<cata;j++)
		{
			cout<<m_matrix[i*cata+j]<<" ";
		}
		cout<<endl;
	}

	cout<<"center:"<<n<<endl;
	for(int i=0;i<cata;i++)
	{
		for(int j=0;j<dimension;j++)
		{
			cout<<m_center[i*dimension+j]<<" ";
		}
		cout<<endl;
	}
	
	n++;
		
}
void CFCM::runFCM()
{
	for(int i=0;i<cata;i++)
	{
		int c = i*numpattern/cata;
		for(int j=0;j<dimension;j++)
			m_center[i*dimension+j]=m_pattern[c*dimension+j];
	}
	for(int i=0;i<numpattern;i++)
	{
		for(int j=0;j<cata;j++)
		{
            m_matrix[i*cata+j]=0;
		}
	}
		
	double lastV = 0;double delta=0;
	int cycle = 0;
	do 
	{
		//dump();
		//=============计算隶属度
		for(int i=0;i<numpattern;i++)
		{
			for(int j=0;j<cata;j++)
			{
				double v1[D];
				double v2[D];
				for(int k=0;k<dimension;k++)
				{
					v1[k] = m_pattern[i*dimension+k];
					v2[k] = m_center[j*dimension+k];
				}
				m_matrix[i*cata+j] = 
				  1.0/((distance(v1,v2,dimension)+1.0)*(distance(v1,v2,dimension)+1.0));
			}
			double temp = 0;
			for(int j=0;j<cata;j++)
			{
				temp+=m_matrix[i*cata+j];
			}
			for(int j=0;j<cata;j++)
			{
				m_matrix[i*cata+j]=m_matrix[i*cata+j]/temp;
			}
		}

		//=============计算新的质心
		for(int i=0;i<cata;i++)
			for(int j=0;j<dimension;j++)
				m_center[i*dimension+j]=0;

		for(int i=0;i<cata;i++)
		{
			double temp = 0;
			for(int j=0;j<numpattern;j++)
			{
				temp+=m_matrix[j*cata+i]*m_matrix[j*cata+i];
			}
			for(int j=0;j<numpattern;j++)
			{
				for(int k=0;k<dimension;k++)
				{
					m_center[i*dimension+k]+=
						m_pattern[j*dimension+k]*m_matrix[j*cata+i]*m_matrix[j*cata+i];
				}
			}
			for(int k=0;k<dimension;k++)
			{
				m_center[i*dimension+k]=m_center[i*dimension+k]/temp;
			}
		}

		double temp = objectfun();
		delta = abs(temp - lastV);
		lastV = temp;
		cycle++;
		cout<<"sse:"<<delta<<endl;
	} while (cycle<=maxcycle&&delta>limit);
	//cout<<"重复次数："<<cycle<<endl;
	//cout<<"SSE是："<<delta<<endl;

}
void CFCM::Import(const vector<double*>& t)
{
	for(int i=0;i<t.size();i++)
	{
		for(int j=0;j<dimension;j++)
			m_pattern[i*dimension+j]=t[i][j];
	}
	cout<<"complete import"<<endl;
}
void CFCM::Export(string filename)
{
	ofstream gen(filename.c_str());
	for(int i=0;i<cata*dimension;i++)
	{
		//gen<<"1"<<endl;
		if(i%dimension==0)
		{
			if(i!=0)gen<<endl;
			gen<<"F"<<i/dimension<<endl;
		}
		   
		gen<<(int)m_center[i]<<" ";
	}
	gen.close();
	//for(int i=0;i<cata*dimension;i++)
	//{
	//	cout<<m_center[i]<<" ";
	//	if(i%dimension==(dimension-1))
	//		cout<<endl;
	//}
}


double CFCM::distance(double* v1,double* v2,int dimen)
{
	double r = 0;
	for(int i=0;i<dimen;i++)
	{
		r+=(v1[i]-v2[i])*(v1[i]-v2[i]);
	}
	return sqrt(r);

}
//=============计算SSE
double CFCM::objectfun()
{
	double sse = 0;
	for(int i=0;i<numpattern;i++)
	{
		for(int j=0;j<cata;j++)
		{
			double v1[D];
			double v2[D];
			for(int k=0;k<dimension;k++)
			{
				v1[k] = m_pattern[i*dimension+k];
				v2[k] = m_center[j*dimension+k];
			}

		    double dis = distance(v1,v2,dimension);
			sse+=dis*dis*m_matrix[i*cata+j]*m_matrix[i*cata+j];
		}
	}

	return sse;
}