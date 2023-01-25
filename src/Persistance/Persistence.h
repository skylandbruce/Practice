#pragma once
#include "Entity.h"


class Persistence {
public:

  Persistence(void);
  ~Persistence(void);
  	
virtual  Entity* fetchEntity(Entity* entity, CString key);
//  void Fetch(EntitySet set, Entity prototype, Condition condition);
virtual  void Fetch(Entity* entity);
virtual  int FetchSet(CPtrArray* setArray, CString fileName){return 0;};
  
virtual  void Insert(Entity* entity);

virtual  void Update(Entity* entity);
virtual  void Update(Entity* entity, CStringList* fieldOrder);
virtual  void UpdateSet(CPtrArray* setArray, CString fileName){};

virtual  void Delete(Entity* entity);

virtual  void Rename(Entity* entity);
//  CMapCStringToOb* getValueTable(Entity* entity);
 
};