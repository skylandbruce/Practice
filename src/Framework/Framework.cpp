#include "StdAfx.h"
#include "Framework.h"

Framework::Framework(void)
{
//	Init();

	Services=new CMapStringToOb();
	RootInfo=new MetaInfo();
}

Framework::~Framework(void)
{
	POSITION pos;
	CString key;
	Service* service;
	pos=Services->GetStartPosition();
	
	while(pos!=NULL)
	{
		Services->GetNextAssoc(pos, key, (CObject*&)service);
		delete service;
	}

    delete p;
	delete kit ;
	delete Services;
}

void Framework::init(void)
{

}
void Framework::registeService(CString name, Service* service)
{
	Services->SetAt(name,(CObject*)service);
}

void Framework::initService(void)
{
	POSITION pos;
	CString key;
	Service* service;
	pos=Services->GetStartPosition();
	
	while(pos!=NULL)
	{
		Services->GetNextAssoc(pos, key, (CObject*&)service);
		service->setEntityKit(kit);
		service->setServices(Services);
	}
}
/*
CString Framework::getRootPath(void)
{
	return RootInfo->getMetaPath();
}
*/
Service* Framework::getService(CString name)
{
	Service* service;
	if(Services->Lookup(name,(CObject*&)service)==0) return NULL;
	return service;
}

void Framework::updateRoot(void)
{
	POSITION pos;
	CString key;
	Service* service;
	pos=Services->GetStartPosition();

	if(RootInfo->getMetaFilter().IsEmpty() == true)
		RootInfo->setMetaFilter(_T("*"));
	
	while(pos!=NULL)
	{
		Services->GetNextAssoc(pos, key, (CObject*&)service);
		service->setRoot(RootInfo);
	}

}