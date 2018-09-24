#pragma once
//#pragma comment(lib,"Ws2_32.lib") 
template<class T>
class CDistance
{
public:
	static T Euclidean(T *t1,T *t2,int n);
	static T CosSimility(T *t1,T *t2,int n);
	static T HistSimility(T *t1,T *t2,int n);
};
