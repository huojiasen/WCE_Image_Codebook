#include "CodeBook.h"
void CCodeBook::ReleaseCodeBook()
{
	//==========��ȡ�ļ�
	vector<string> ImageName;
	_finddata_t file;long lf;
	string url = m_dir+"*.jpg";
	if((lf=_findfirst(url.c_str(),&file))==-1)
		cout<<"no path!"<<endl;
	else
	{
		do 
		{
			ImageName.push_back(file.name);
			cout<<"add file : "<<file.name<<endl;
		} while (_findnext(lf,&file)==0);
	}
	_findclose(lf);
	//==========��ȡ����
	vector<double*> fes; fes.clear();
	for(int i=0;i<ImageName.size();i++)
	{
		string name = m_dir+ImageName[i];
		cout<<name<<endl;
		IplImage *src = cvLoadImage(name.c_str());
		m_slient->CalSalient(src);//1
		for(int j=0;j<m_slient->getResult().size();j++)
		{
			_res r = m_slient->getResult()[j];
			_point p = r.s;
			int w = r.w; int h = r.h;
			CvRect mask = cvRect(p.y,p.x,w,h);
			IplImage *dst = cvCreateImage(cvSize(w,h),8,3);
			cvSetImageROI(src,mask);
			cvCopy(src,dst);
			cvResetImageROI(src);
			m_feature->extract(dst);//2
			double *temp = new double[192];
			double* t = m_feature->getFeature();
			for(int i=0;i<192;i++)
			{
				temp[i]=t[i];
			}
			fes.push_back(temp);
			cvReleaseImage(&dst);
		}
		cvReleaseImage(&src);
	}
	//==========�����뱾

	int n = fes.size();
	m_fcm = new CFCM(n,192,192,20,0,0.1);//n������ 192ά 192������ ���20�� sse0.1
	m_fcm->Import(fes);
	for(int i=0;i<fes.size();i++)
	{
		delete []fes[i];fes[i]=NULL;
	}
	fes.clear();
	try 
	{
		m_fcm->runFCM();//3
	}
	catch(std::bad_alloc &excp) 
	{
		//print("error: %s", excp.what());
		cout<<"error:"<<excp.what();
	} 
	m_fcm->Export();

}