#include "ColorBuilder.h"
#include "Gabor.h"
Document* CColorBuilder::createDocument(IplImage *image,string name)
{
	m_vd = new CGabor();
	m_vd->extract(image);
	string featureString = m_vd->getStringRepresentation();
	cout<<name<<":"<<featureString<<endl;
	const char *s = featureString.c_str();
	TCHAR *tbuf = new TCHAR[featureString.size()];
	STRCPY_AtoT(tbuf,s,featureString.size());
	StringBuffer str;
	str.append(tbuf);
	m_doc.add(*_CLNEW Field(_T("featureGABOR"),str.getBuffer(), Field::STORE_YES | Field::INDEX_TOKENIZED));
	if(name.size()!=0)
	{
		const char *n = name.c_str();
		TCHAR *nbuf = new TCHAR[name.size()];
		STRCPY_AtoT(nbuf,n,name.size());
		StringBuffer ntr;
		ntr.append(nbuf);
		m_doc.add(*_CLNEW Field(_T("pathname"),ntr.getBuffer(), Field::STORE_YES | Field::INDEX_TOKENIZED));

	}
	return &m_doc;
}