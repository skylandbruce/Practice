#pragma once
#include "Entity.h"


class DIR : public Entity
{
protected: 
//	DIR* prototype;
	MetaInfo* metaInfo;
	CStringList* DirList;
	CStringList* FileList;
public:
	DIR(void);
	~DIR(void);

//  static Entity* getPrototype();
  DIR* getInstance(void);
  MetaInfo* getMetaInfo();

};
