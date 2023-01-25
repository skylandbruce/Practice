#pragma once
#include "Entity.h"
#include "MetaInfo.h"

class MIN : public Entity
{
protected:
	MIN* prototype;
	MetaInfo* metaInfo;
public:
	MIN(void);
	~MIN(void);

//	static Entity* getPrototype();
	Entity* getInstance();
	MetaInfo* getMetaInfo();
};
