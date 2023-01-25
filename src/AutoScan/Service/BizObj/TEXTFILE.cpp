#include "StdAfx.h"
#include "TEXTFILE.h"


TEXTFILE::TEXTFILE(void)
{
	metaInfo = new MetaInfo(CString("TEXTFILE"));
//	metaInfo->setMetaFileName(_T("*.*"));
}

TEXTFILE::~TEXTFILE(void)
{
}

TEXTFILE* TEXTFILE::getInstance() {

	TEXTFILE* file=new TEXTFILE();

	CStringList* buffer=new CStringList();
	file->registerField(_T("buffer"),(CObject*) buffer);

	return (TEXTFILE*)file;
}

MetaInfo* TEXTFILE::getMetaInfo() {
	return (MetaInfo*)metaInfo;
}

