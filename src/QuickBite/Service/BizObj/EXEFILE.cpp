#include "StdAfx.h"
#include "EXEFILE.h"


EXEFILE::EXEFILE(void)
{
	metaInfo = new MetaInfo(CString("EXEFILE"));
}

EXEFILE::~EXEFILE(void)
{
}

EXEFILE* EXEFILE::getInstance() {

	EXEFILE* file=new EXEFILE();
	CString* Title=new CString(_T("QuickBite"));
	CString* imageset=new CString(_T(""));
	CString* order=new CString(_T("0"));

	file->registerField(_T("title"),(CObject*) Title);
	file->registerField(_T("imageset"),(CObject*) imageset);
	file->registerField(_T("order"),(CObject*) imageset);

	return (EXEFILE*)file;
}

MetaInfo* EXEFILE::getMetaInfo() {
	return (MetaInfo*)metaInfo;
}

