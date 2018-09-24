#include "Distance.h"
#include <math.h>
template<class T>
    T CDistance<T>::Euclidean(T *t1,T *t2,int n)
{
	T d = 0;
	for(int i=0;i<n;i++)
	{
		d+=(t1[i]-t2[i])*(t1[i]-t2[i]);
	}
	d = sqrt(d);
	return d;
}
template<class T>
   T CDistance<T>::CosSimility(T *t1,T *t2,int n)
{
	T d =0,x=0,y=0;
	for(int i=0;i<n;i++)
	{
		d+=t1[i]*t2[i];
		x+=t1[i]*t1[i];
		y+=t2[i]*t2[i];
	}
	d = d/(sqrt(x)*sqrt(y));
	return d;
}
template<class T>
   T CDistance<T>::HistSimility(T *t1,T *t2,int n)
{
	T d = 0;
	for(int i=0;i<n;i++)
	{
		d+= fabs(t1[i]-t2[i])/(t1[i]+t2[i]+1);
	}
	return d;
}
