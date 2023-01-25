#pragma once
#include "EntityKit.h"

class Service
{
protected:
	EntityKit* Kit;
	MetaInfo* RootInfo;
	CString RootPath;
	CMapStringToOb* Services;
public:
	Service(void);
	~Service(void);
	void setEntityKit(EntityKit* kit);
	void setServices(CMapStringToOb* services);
	void setRoot(MetaInfo* Info);
	Service* getService(CString name);
};
