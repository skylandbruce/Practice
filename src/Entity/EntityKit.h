#pragma once
#include "Persistence.h"
#include "Entity.h"
#include "UtilString.h"

class EntityKit{

protected:
	Persistence* persister;
	CMapStringToOb* entityPrototypes; // entity_name, entity_object
	CMapStringToOb* entityCache;
	CMapStringToOb* EntitySetPool;

public:

	EntityKit();
	EntityKit(Persistence* p);
	~EntityKit();

	Persistence* getPersistence();
	void registerEntityPrototype(Entity* prototype);
//	Entity* getNewEntity(CString entityName, CString key);
	Entity* getNewEntity(Entity* originProto, CString key);
	Entity* getEntity(CString key);
	Entity* getPrototype(CString entityName);

	CMapStringToOb* getEntitySet(Entity* prototype);
	CMapStringToOb* getEntitySet(Entity* prototype, Entity* relativeEntity, CString relation);
	CPtrArray* getArrayEntitySet(Entity* prototype, CString Order=_T(""), bool isIncrease=true);




/*
	EntitySet EntityKit::getEntitySet(CString entityName, Condition condition);
	EntitySet EntityKit::getEntitySet(CString entityName, Condition condition, CString orderByField, boolean ascend);
	EntitySet EntityKit::getEntitySet(EntitySet set, CString entityName, Condition condition);
	Condition EntityKit::onlyNewEntityCondition(EntitySet exclusive, Condition condition);
*/
	void Cache(Entity* entity);
	void Insert(Entity* entity);
	void Update(Entity* entity);
	void Delete(Entity* entity);
//	static CString EntityKit::getKeyPrefix(CString key);
	friend void UtilString::splitFileName(CString* FileName, CString* Ext);
	friend bool	UtilString::isSubSet(CString fullset, CString subset);
static   bool isValidFile(Entity* prototype, CString FileName);

};