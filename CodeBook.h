#pragma once
#include "LireFeature.h"
#include "Fcth.h"
#include "Slient.h"
#include "FCM.h"
#include <io.h>
class CCodeBook
{
private:
	iLireFeature* m_feature;
	CSlient*      m_slient;
	CFCM*         m_fcm;
	string        m_dir;
public:
	CCodeBook(string dir):m_dir(dir)
	{
        m_feature = new CFcth();
		m_slient = new CSlient();
		//m_fcm = new CFCM();
	}
	~CCodeBook(void)
	{
		delete m_feature;m_feature = NULL;
		delete m_slient;m_slient = NULL;
		delete m_fcm;m_fcm = NULL;
	}
public:
	void ReleaseCodeBook();
};
