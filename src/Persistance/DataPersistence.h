#pragma once

#include "persistence.h"
class DataPersistence :	public Persistence
{
protected:
	CFile File;
	CFileException e;

	BOOL OpenFile(CString FileName, CString Mode);
public:
	DataPersistence(void);
	~DataPersistence(void);

   Entity* fetchEntity(Entity* entity, CString key);

//   void Fetch(EntitySet set, Entity prototype, Condition condition);
   void Fetch(Entity* entity);  
	int FetchSet(CPtrArray* setArray, CString fileName);

   void Insert(Entity* entity);

   void Update(Entity* entity);
   void Update(Entity* entity, CStringList* fieldOrder);
	void UpdateSet(CPtrArray* setArray, CString fileName);

   void Delete(Entity* entity);

	void Rename(Entity* entity);
};
