#pragma once
#include "LireFeature.h"
#include "LuceneHeader.h"
const string FIELD_NAME_COLORHISTOGRAM = "featureColor";
const string FIELD_NAME_BEDD = "featureBEDD";
const string FIELD_NAME_LAWS = "featureLAWS";
const string FIELD_NAME_GABOR = "featureGABOR";
const string FIELD_NAME_FCTH = "featureFCTH";
class iDocumentBuilder
{
protected:
	iLireFeature* m_vd;
public:
	virtual ~iDocumentBuilder()=0{};
	virtual Document* createDocument(IplImage *image,string name)=0;
};
