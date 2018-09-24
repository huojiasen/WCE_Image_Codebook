#pragma once
#include "ImageSearcher.h"
#include "SimpleSearcher.h"
#include "CodeSearcher.h"
class CImageSearcherFactory
{
public:
	static iImageSearcher* getSimpleSearcher()
	{
		return new CSimpleSearcher();
	}
	static iImageSearcher* getCodeSearcher()
	{
		return new CCodeSearcher();
	}
};
