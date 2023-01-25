#include "StdAfx.h"
#include "IncludeMIN.h"

IncludeMIN::IncludeMIN(void)
{
	metaInfo = new MetaInfo(CString("IncludeMIN"));
}

IncludeMIN::~IncludeMIN(void)
{
	delete metaInfo;

}
/*
Entity* IncludeMIN::getPrototype() {
	if (prototype == NULL) {
	  prototype = new IncludeMIN();
	  prototype->metaInfo = new MetaInfo(CString("IncludeMIN"));
	}
	return (Entity*)prototype;
}
*/


Entity* IncludeMIN::getInstance() {
	IncludeMIN* min=new IncludeMIN();

	CString headerStr(_T("// Created by AutoScan1.0\r\n"));
	CString rootStr(_T("\r\nSRCROOT="));

	CString pathsStr(_T("\r\n"));
	CString allpathsStr(_T("\r\nALL_PATHS=\\\r\n\t"));
	CString incprefixStr(_T("\r\nINCLUDE_PREFIX = -I\r\n"));
	CString allincludesStr(_T("\r\nALL_INCLUDES = $(addprefix $(INCLUDE_PREFIX), $(ALL_PATHS))\r\n"));

	CStringList * header;
	CStringList * root;
	CStringList * paths;
	CStringList * allpaths;
	CStringList * incprefix;
	CStringList * allincludes;

	header = new CStringList();
	header->AddTail(headerStr);

	root = new CStringList();
	root->AddTail(rootStr);

	paths = new CStringList();
	paths->AddTail(pathsStr);

	allpaths = new CStringList();
	allpaths->AddTail(allpathsStr);

	incprefix = new CStringList();
	incprefix->AddTail(incprefixStr);

	allincludes = new CStringList();
	allincludes->AddTail(allincludesStr);

	min->registerField(_T("header"),(CObject*) header);
	min->registerField(_T("root"),(CObject*) root);
	min->registerField(_T("paths"),(CObject*) paths);
	min->registerField(_T("allpaths"),(CObject*) allpaths);
	min->registerField(_T("incprefix"),(CObject*) incprefix);
	min->registerField(_T("allincludes"),(CObject*) allincludes);

	return (Entity*)min;
}

MetaInfo* IncludeMIN::getMetaInfo() {
	return (MetaInfo*)metaInfo;
}