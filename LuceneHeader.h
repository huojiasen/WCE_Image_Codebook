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
//int buff[M]={0}; //缓冲区大小为10
//int in=0;
//int out=0;
//
//int prod_id=0;
//int proc_id=0;
//
//HANDLE EemptySem=NULL; //同步信号量， 当满了时阻止生产者放产品
//HANDLE FullSem=NULL;   //同步信号量， 当没产品时阻止消费者消费
//HANDLE hMutex=NULL;    //线程互斥，一次一个线程访问缓冲区
//
//void print();//打印缓冲区
//UINT _stdcall ThreadProd(LPVOID);//生产者线程入口函数
//UINT _stdcall ThreadProc(LPVOID);//消费者线程入口函数
//
//void main()
//{
//	UINT uId;
//	HANDLE prodh[N];
//	HANDLE proch[N];
//	EemptySem=CreateSemaphore(NULL,10,10,NULL);// 初始化为10，最大值为 10，当等于0时，表示换冲区满了，今天这里丢人了
//	FullSem=CreateSemaphore(NULL,0,10,NULL);//
//	hMutex=CreateSemaphore(NULL,1,1,NULL);  // 初始化为1的信号量实现线程互斥
//
//	int i;
//	//创建N个生产者
//	for(i=0;i<N;i++)
//	{
//		prodh[i]=(HANDLE)::_beginthreadex(NULL,0,ThreadProd,NULL,0,&uId);
//
//	}
//
//	//创建N个消费者
//	for(i=0;i<N;i++)
//	{
//		prodh[i]=(HANDLE)::_beginthreadex(NULL,0,ThreadProc,NULL,0,&uId);
//
//	}
//	// 销毁线程
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
//		Sleep(1000); //停留一秒，这里和linux下不一样
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
////打印缓冲区
//void print()
//{
//	int i;
//	for(i = 0; i < M; i++)
//		printf("%d ", buff[i]);
//	printf("\n");
//}