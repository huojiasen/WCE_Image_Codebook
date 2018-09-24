#pragma once
#include <string>
#include <iostream>
#include <strstream>
#include <io.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#pragma comment(lib,"cv200.lib")
#pragma comment(lib,"cxcore200.lib")
#pragma comment(lib,"highgui200.lib")
using namespace std;
class iLireFeature
{
public:
	virtual void extract(IplImage *image)=0;
	virtual string getStringRepresentation()=0;
	virtual double* getFeature() const = 0;
	virtual ~iLireFeature(){};
};