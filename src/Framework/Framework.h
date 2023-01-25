#pragma once
#include "Persistence.h"
#include "EntityKit.h"
#include "Service.h"

class Framework
{
protected:
	Persistence *p;
	EntityKit	*kit;
	MetaInfo* RootInfo;

//	CString RootPath;

	CMapStringToOb* Services;
public:
	Framework(void);
	~Framework(void);
	// 오버라이드 함수
	void init(void);
	void registeService(CString name, Service* service);
	void initService(void);
//	CString getRootPath(void);
	Service* getService(CString name);

	void updateRoot(void);
};
