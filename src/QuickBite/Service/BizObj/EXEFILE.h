#pragma once
#include "Entity.h"


class EXEFILE : public Entity
{
protected: 
//	EXEFILE* prototype;
	MetaInfo* metaInfo;

public:
	EXEFILE(void);
	~EXEFILE(void);

//  static Entity* getPrototype();
  EXEFILE* getInstance(void);
  MetaInfo* getMetaInfo();

};
