

#include "persistence.h"
class FilePersistence :	public Persistence
{
protected:
	CFile File;
	CFileException e;

	BOOL OpenFile(CString FileName, CString Mode);
public:
	FilePersistence(void);
	~FilePersistence(void);

   Entity* fetchEntity(Entity* entity, CString key);

//   void Fetch(EntitySet set, Entity prototype, Condition condition);
   void Fetch(Entity* entity);  

   void Insert(Entity* entity);

   void Update(Entity* entity);
   void Update(Entity* entity, CStringList* fieldOrder);

   void Delete(Entity* entity);

	void Rename(Entity* entity);
};
