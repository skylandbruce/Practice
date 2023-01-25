#include "StdAfx.h"
#include "DIR.h"


DIR::DIR(void)
{
	metaInfo = new MetaInfo(CString("DIR"));
	metaInfo->setMetaFileName(_T("*.*"));
}

DIR::~DIR(void)
{
}

/*
Entity* DIR::getPrototype() {
	if (prototype == NULL) {
	  prototype = new DIR();
	  prototype->metaInfo = new MetaInfo(CString("DIR"));
	}
	return (Entity*)&prototype;
}
*/

DIR* DIR::getInstance() {

	DIR* dir=new DIR();
//	dir->metaInfo->setMetaPath(FullpathName);

	CStringList* DirList=new CStringList();
	CStringList* FileList=new CStringList();

	dir->registerField(_T("dir"),(CObject*) DirList);
	dir->registerField(_T("file"),(CObject*) FileList);

	return (DIR*)dir;
}

MetaInfo* DIR::getMetaInfo() {
	return (MetaInfo*)metaInfo;
}

