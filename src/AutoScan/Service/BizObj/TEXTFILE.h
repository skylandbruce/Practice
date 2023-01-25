#pragma once
#include "Entity.h"


class TEXTFILE : public Entity
{
protected: 
//	TEXTFILE* prototype;
	MetaInfo* metaInfo;

public:
	TEXTFILE(void);
	~TEXTFILE(void);

//  static Entity* getPrototype();
  TEXTFILE* getInstance(void);
  MetaInfo* getMetaInfo();

};
