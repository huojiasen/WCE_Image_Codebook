#pragma once
#include "DocumentBuilder.h"
#include "ColorBuilder.h"
#include "FCTHBuilder.h"
class CBuilderFactory
{
public:
	static iDocumentBuilder* getColorBuilder()
	{
		return new CColorBuilder();
	}
	static iDocumentBuilder* getFCTHBuilder()
	{
		return new CFCTHBuilder();
	}
};
