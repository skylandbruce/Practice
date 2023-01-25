#include "StdAfx.h"
#include "MIN.h"

MIN::MIN(void)
{
	metaInfo = new MetaInfo(CString("MIN"));
}

MIN::~MIN(void)
{
	delete metaInfo;

}
/*
Entity* MIN::getPrototype() {
	if (prototype == NULL) {
	  prototype = new MIN();
	  prototype->metaInfo = new MetaInfo(CString("MIN"));
	}
	return (Entity*)prototype;
}
*/


Entity* MIN::getInstance() {
	MIN* min=new MIN();

	CString srcc(_T("AUTODIR_C_SOURCES=\\\r\n"));
	CString srcs(_T("\r\nAUTODIR_S_SOURCES=\\\r\n"));
	CString src(_T("\r\nAUTODIR_SOURCES=\\\r\n\t $(AUTODIR_C_SOURCES)\\\r\n\t $(AUTODIR_A_SOURCES)\r\n"));
	CString objs(_T("\r\nAUTODIR_OBJS := $(addprefix $(TARGETDIR)/, $(AUTODIR_C_SOURCES:%.c=%.o) $(AUTODIR_A_SOURCES:%.s=%.o))\r\n"));
	CString vpathc(_T("\r\nvpath %.c $(AUTODIR)"));
	CString vpaths(_T("\r\nvpath %.s $(AUTODIR)"));

	CStringList * format;
	format = new CStringList();
	format->AddTail(srcc);
	format->AddTail(srcs);
	format->AddTail(src);
	format->AddTail(objs);
	format->AddTail(vpathc);
	format->AddTail(vpaths);

	min->registerField(_T("format"),(CObject*) format);


/*
	min->registerField(_T("srcc"),(CObject*) &srcs);
	min->registerField(_T("srcs"),(CObject*) &srcs);
	min->registerField(_T("src"),(CObject*) &src);
	min->registerField(_T("objs"),(CObject*) &objs);
	min->registerField(_T("vpathc"),(CObject*) &vpathc);
	min->registerField(_T("vpaths"),(CObject*) &vpaths);
*/
//	min->metaInfo->setMetaFullPathName(FullpathName);

	return (Entity*)min;
}

MetaInfo* MIN::getMetaInfo() {
	return (MetaInfo*)metaInfo;
}