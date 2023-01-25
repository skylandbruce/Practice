#include "StdAfx.h"
#include "Persistence.h"


Persistence::Persistence() 
{
}

Persistence::~Persistence() 
{
}



  Entity* Persistence::fetchEntity(Entity* entity, CString key){return entity;}

//  void Persistence::Fetch(EntitySet set, Entity prototype, Condition condition){}
  void Persistence::Fetch(Entity* entity){}
    
  void Persistence::Insert(Entity* entity){}

  void Persistence::Update(Entity* entity){}
  void Persistence::Update(Entity* entity, CStringList* fieldOrder){}

  void Persistence::Delete(Entity* entity) {}

  void Persistence::Rename(Entity* entity){}
/*
  CMapCStringToOb* Persistence::getValueTable(Entity* entity) 
  {
    return entity->getValueTable();
  }
*/  

