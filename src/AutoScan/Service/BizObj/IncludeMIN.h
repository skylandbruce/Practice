#pragma once
#include "Entity.h"
#include "MetaInfo.h"

class IncludeMIN : public Entity
{
protected:
	IncludeMIN* prototype;
	MetaInfo* metaInfo;
public:
	IncludeMIN(void);
	~IncludeMIN(void);

//	static Entity* getPrototype();
	Entity* getInstance();
	MetaInfo* getMetaInfo();
};
