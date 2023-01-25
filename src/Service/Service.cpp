#include "StdAfx.h"
#include "Service.h"

Service::Service(void)
{
}

Service::~Service(void)
{
}

void Service::setEntityKit(EntityKit* kit)
{
	Kit=kit;
}

void Service::setServices(CMapStringToOb* services)
{
	Services=services;
}

Service* Service::getService(CString name)
{
	Service* service;
	Services->Lookup(name, (CObject*&)service);
	return service;
}

void Service::setRoot(MetaInfo* Info)
{
	RootInfo=Info;
	RootPath=Info->getMetaPath();
}