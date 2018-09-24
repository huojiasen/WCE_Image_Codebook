#pragma once
#include "CLucene/StdHeader.h"
#include "CLucene/_clucene-config.h"
#include "CLucene.h"
#include "CLucene/util/CLStreams.h"
#include "CLucene/util/dirent.h"
#include "CLucene/config/repl_tchar.h"
#include "CLucene/util/Misc.h"
#include "CLucene/util/StringBuffer.h"
#include "CLucene/config/repl_wchar.h"
#pragma comment(lib,"clucene-cored.lib")
#pragma comment(lib,"clucene-sharedd.lib")
using namespace std;
using namespace lucene::index;
using namespace lucene::analysis;
using namespace lucene::util;
using namespace lucene::store;
using namespace lucene::document;
using namespace lucene::queryParser;
using namespace lucene::search;
//#include <Windows.h>
//#include <stdio.h>
//int a;
//int b;
//int c;
//DWORD WINAPI ThreadFun(LPVOID lParam)
//{
//	a = (int)lParam;
//	b = (int)lParam;
//	Sleep(10);
//	c = (int)lParam;
//    int n = a*b*c;
//
//	printf("%d\n",n);
//
//	return 0;
//}
//void main()
//{
//	HANDLE hThread[2];
//	DWORD dwID;
//	for(int i=0;i<2;i++)
//	{ 
//		hThread[i]=::CreateThread(NULL,0,ThreadFun,(LPVOID)i,0,&dwID);
//
//	}
//	::WaitForMultipleObjects(2,hThread,TRUE,INFINITE);
//
//	::CloseHandle(hThread[0]);
//	::CloseHandle(hThread[1]);
//	getchar();
//}
//#include<stdio.h>
//#include<windows.h>
//#include<process.h>
//
//#define N 2
//#define M 10
//
//int buff[M]={0}; //��������СΪ10
//int in=0;
//int out=0;
//
//int prod_id=0;
//int proc_id=0;
//
//HANDLE EemptySem=NULL; //ͬ���ź����� ������ʱ��ֹ�����߷Ų�Ʒ
//HANDLE FullSem=NULL;   //ͬ���ź����� ��û��Ʒʱ��ֹ����������
//HANDLE hMutex=NULL;    //�̻߳��⣬һ��һ���̷߳��ʻ�����
//
//void print();//��ӡ������
//UINT _stdcall ThreadProd(LPVOID);//�������߳���ں���
//UINT _stdcall ThreadProc(LPVOID);//�������߳���ں���
//
//void main()
//{
//	UINT uId;
//	HANDLE prodh[N];
//	HANDLE proch[N];
//	EemptySem=CreateSemaphore(NULL,10,10,NULL);// ��ʼ��Ϊ10�����ֵΪ 10��������0ʱ����ʾ���������ˣ��������ﶪ����
//	FullSem=CreateSemaphore(NULL,0,10,NULL);//
//	hMutex=CreateSemaphore(NULL,1,1,NULL);  // ��ʼ��Ϊ1���ź���ʵ���̻߳���
//
//	int i;
//	//����N��������
//	for(i=0;i<N;i++)
//	{
//		prodh[i]=(HANDLE)::_beginthreadex(NULL,0,ThreadProd,NULL,0,&uId);
//
//	}
//
//	//����N��������
//	for(i=0;i<N;i++)
//	{
//		prodh[i]=(HANDLE)::_beginthreadex(NULL,0,ThreadProc,NULL,0,&uId);
//
//	}
//	// �����߳�
//	for(i=0;i<N;i++)
//	{
//		WaitForSingleObject(prodh[i],INFINITE);
//		WaitForSingleObject(proch[i],INFINITE);
//
//		::CloseHandle(prodh[i]);
//		::CloseHandle(proch[i]);
//
//
//	}
//
//
//
//}
//
//
//UINT _stdcall ThreadProd(LPVOID)
//{
//	int id=++prod_id;
//	while(1)
//	{
//		Sleep(1000); //ͣ��һ�룬�����linux�²�һ��
//		WaitForSingleObject(EemptySem,INFINITE);
//		WaitForSingleObject(hMutex,INFINITE);
//		in = in % M;
//		printf("product%d into %d: \t", id, in);
//		buff[in] = 1;  
//		print();  
//		++in;
//		ReleaseSemaphore(hMutex,1,NULL);
//		ReleaseSemaphore(FullSem,1,NULL);
//	}
//
//
//}
//
//UINT _stdcall ThreadProc(LPVOID)
//{
//	int id=++proc_id;
//	while(1)
//	{
//		Sleep(1000);
//		WaitForSingleObject(FullSem,INFINITE);
//		WaitForSingleObject(hMutex,INFINITE);
//
//		out=out%M;
//		printf("prochase%d outfrom %d: \t", id, out);
//		buff[out] = 0;
//		print();
//		++out;
//
//		ReleaseSemaphore(hMutex,1,NULL);
//		ReleaseSemaphore(EemptySem,1,NULL);
//	}
//
//}
////��ӡ������
//void print()
//{
//	int i;
//	for(i = 0; i < M; i++)
//		printf("%d ", buff[i]);
//	printf("\n");
//}