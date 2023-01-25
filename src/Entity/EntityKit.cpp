#include "StdAfx.h"
#include "EntityKit.h"


EntityKit::EntityKit()
{
}

EntityKit::~EntityKit()
{

	POSITION pos;
	Entity* entity;
	CStringList* entitySet;
	CString key;



	pos=entityPrototypes->GetStartPosition();	
	while(pos!=NULL)
	{
		entityPrototypes->GetNextAssoc(pos, key, (CObject*&)entity);
		delete entity;
	}

	pos=entityCache->GetStartPosition();	
	while(pos!=NULL)
	{
		entityCache->GetNextAssoc(pos, key, (CObject*&)entity);
		delete entity;
	}


	pos=EntitySetPool->GetStartPosition();	
	while(pos!=NULL)
	{
		EntitySetPool->GetNextAssoc(pos, key, (CObject*&)entitySet);
		delete entitySet;
	}


	delete entityPrototypes;
	delete entityCache;
	delete EntitySetPool;
}

/*
EntityKit:: EntityKit(Persistence p, long cacheExpirationTime) {
    persister = p;
    unique = UniqueGenerator.instance();
    cache = new EntityCache(cacheExpirationTime, 30000);
    entityPrototypes = new CMapStringToOb();
  }
*/
EntityKit:: EntityKit(Persistence* p) {
    persister = p;
    entityPrototypes = new CMapStringToOb();
	entityCache= new CMapStringToOb();
	EntitySetPool = new CMapStringToOb();
  }


  Persistence* EntityKit::getPersistence() {
    return persister;
  }

  void EntityKit::registerEntityPrototype(Entity* prototype) {
    entityPrototypes->SetAt(prototype->getEntityName(), (CObject*)prototype);
  }

// Deplicatied
/*
  Entity* EntityKit::getNewEntity(CString entityName, CString key) {
    Entity *prototype; 
	Entity* entity;

	if(entityPrototypes->Lookup(entityName,(CObject*&)prototype)==0)
		return NULL;

	// 존재하지 않는 entity 이면 새로 Instance를 생성
	if (entityCache->Lookup(key,(CObject*&)entity)==0)
	{
		entity= prototype->getInstance();

		entity->setKey(key);
		Cache(entity);
	}
    return entity;
  }
*/

Entity* EntityKit::getNewEntity(Entity* originProto, CString key) {
    Entity *prototype; 
	Entity* entity;

	if(entityPrototypes->Lookup(originProto->getEntityName(),(CObject*&)prototype)==0)
		return NULL;


	// 존재하지 않는 entity 이면 새로 Instance를 생성
	if (entityCache->Lookup(key,(CObject*&)entity)==0)
	{
		entity= prototype->getInstance();

		entity->setKey(key);
	}
    return entity;
}

  Entity* EntityKit::getEntity(CString key){

      CObject* entity;
	  entityCache->Lookup(key,(CObject*&)entity);

    return (Entity*)entity;
  }

  Entity* EntityKit::getPrototype(CString entityName){

      CObject* prototype;
	  entityPrototypes->Lookup(entityName,(CObject*&)prototype);

    return (Entity*)prototype;
  }

// prototype 의 조건에 만족하는 Entity Set을 얻음
CMapStringToOb* EntityKit::getEntitySet(Entity* prototype)
{
	POSITION pos;
	Entity* cacheEntity;
	CString key;
	CString setkey;
	CMapStringToOb* entitySet; 

	CString FileName;
	CString EntityName;

	setkey=prototype->getKey();

	// Pool 에 존재하지 않으면
	if( EntitySetPool->Lookup(setkey, (CObject*&)entitySet) == 0 )
	{
		entitySet= new CMapStringToOb();
		
		pos=entityCache->GetStartPosition();	
		while(pos!=NULL)
		{
			entityCache->GetNextAssoc(pos, key, (CObject*&)cacheEntity);

			EntityName=cacheEntity->getEntityName();


			if(EntityName.Compare(prototype->getEntityName()) == 0)
			{
				if(EntityName.Compare(_T("DIR"))==0)
					FileName=cacheEntity->getMetaInfo()->getMetaDirName();
				else
					FileName=cacheEntity->getMetaInfo()->getMetaFileName();

				if( isValidFile(prototype, FileName) ==true)
				{
					entitySet->SetAt(cacheEntity->getKey(), (CObject*)cacheEntity);
				}
			}
		}
		if(entitySet->IsEmpty() ==false)
//		{
//			delete entitySet;
//			entitySet=NULL;  // 함수 호출자는 NULL인지 체크해야 한다
//		}
//		else
		{
			EntitySetPool->SetAt(setkey, entitySet);
		}
	}
	return entitySet;
}


 CMapStringToOb* EntityKit::getEntitySet(Entity* prototype, Entity* relativeEntity, CString relation)
{
	POSITION pos;
	Entity* cacheEntity;
	CString key;
	CString setkey;
	CMapStringToOb* entitySet; 

	CString FileName;
	CString EntityName;

	CString relativeName;

	setkey=prototype->getKey()+relativeEntity->getKey()+relation;

	// Pool 에 존재하지 않으면
	if( EntitySetPool->Lookup(setkey, (CObject*&)entitySet) == 0 )
	{
		entitySet= new CMapStringToOb();
		
		pos=entityCache->GetStartPosition();	
		while(pos!=NULL)
		{
			entityCache->GetNextAssoc(pos, key, (CObject*&)cacheEntity);

			EntityName=cacheEntity->getEntityName();
			if(EntityName.Compare(prototype->getEntityName()) == 0)
			{
				if(relation.Compare(_T("inpath"))==0)
				{
					relativeName=relativeEntity->getMetaInfo()->getMetaPath();
					if(relativeName.Compare(cacheEntity->getMetaInfo()->getMetaPath()) != 0)
						continue;
				}
				// 동일 path는 포함하지 않는다
				if(relation.Compare(_T("subpath"))==0)
				{
					if(UtilString::isSubSet(relativeName+_T("*"), cacheEntity->getMetaInfo()->getMetaPath()) == false)
						continue;
				}

				if(EntityName.Compare(_T("DIR"))==0)
					FileName=cacheEntity->getMetaInfo()->getMetaDirName();
				else
					FileName=cacheEntity->getMetaInfo()->getMetaFileName();

				if( isValidFile(prototype, FileName) ==true)
				{
					entitySet->SetAt(cacheEntity->getKey(), (CObject*)cacheEntity);
				}
			}
		}
		if(entitySet->IsEmpty() ==false)
//		{
//			delete entitySet;
//			entitySet=NULL;  // 함수 호출자는 NULL인지 체크해야 한다
//		}
//		else
		{
			EntitySetPool->SetAt(setkey, entitySet);
		}
	}
	return entitySet;
}


CPtrArray* EntityKit::getArrayEntitySet(Entity* prototype, CString Order, bool isIncrease)
{
	POSITION pos;
	Entity* cacheEntity;
	CString key;
	CString orderField;

	CString EntityName;

	CPtrArray* orderSet=new CPtrArray();
	orderSet->SetSize(0, 20);

	Entity* setEntity;
	CString setOrder;
	CString cacheOrder;

	int i;

	if(Order.IsEmpty()==true)
		orderField=_T("key");
	else
		orderField=Order;

		pos=entityCache->GetStartPosition();	
		while(pos!=NULL)
		{
			entityCache->GetNextAssoc(pos, key, (CObject*&)cacheEntity);

			EntityName=cacheEntity->getEntityName();
			if(EntityName.Compare(prototype->getEntityName()) == 0)
			{							
				for(i=0; i<orderSet->GetCount(); i++)
				{
					setEntity= (Entity*)((*orderSet)[i]);

					if(orderField.Compare(_T("key"))==0)
					{
						setOrder=setEntity->getKey();
						cacheOrder=cacheEntity->getKey();
					}
					else
					{
						setOrder=*((CString*)(setEntity->getValue(orderField)));
						cacheOrder=*((CString*)(cacheEntity->getValue(orderField)));
					}

					if(isIncrease==true)
					{
						if(cacheOrder.Compare(setOrder)<0)
						{
							orderSet->InsertAt(i, cacheEntity);
							break;
						}
					}
					else
					{
						if(cacheOrder.Compare(setOrder)>=0)
						{
							orderSet->InsertAt(i+1, cacheEntity);
							break;
						}
					}
				}//for
				//if(orderSet->IsEmpty()==TRUE)
				if(i >= orderSet->GetCount())
				{
					orderSet->Add(cacheEntity);
				}
				
			}
		}


	return orderSet;
}


/*
// BizObj 의 EntityName이 같은 BizObj들을 Set으로 만들어 Pool에 추가
  CMapStringToOb* EntityKit::getEntitySet(CString EntityName)
{
	POSITION pos;
	Entity* entity;
	CString key;
	CString setkey;
	CMapStringToOb* entitySet; 

	setkey=EntityName;

	// Pool 에 존재하지 않으면
	if( EntitySetPool->Lookup(key, (CObject*&)entitySet) == 0 )
	{

		entitySet= new CMapStringToOb();
		
		pos=entityCache->GetStartPosition();	
		while(pos!=NULL)
		{
			entityCache->GetNextAssoc(pos, key, (CObject*&)entity);
			if(EntityName.Compare(entity->getEntityName()) == 0)
			{
					// 모든 내용을 entitySet으로 반환
				entitySet->SetAt(entity->getKey(), (CObject*)entity);
			}

		}
		if(entitySet->IsEmpty() ==TRUE)
		{
			delete entitySet;
			entitySet=NULL;  // 함수 호출자는 NULL인지 체크해야 한다
		}
		else
		{
			EntitySetPool->SetAt(setkey, entitySet);
		}
	}
	return entitySet;
}
*/

/*
// (Entity*, _T("from dir/file include/exclude/* c s cpp"))
// 하나의 BizObj안에서 특정 field list를 조건검사한 결과 List 얻기
CStringList* EntityKit::getEntitySet(Entity* entity, CString Condition)
{
	POSITION pos;
	CString key;

	CStringList* entitySet;
	CStringList* entityList;
	CString FieldValue;
	CString setkey;

//	MetaInfo meta;

	CString from;
	CString with;
	CString filter;

	int tokenPos=0;
	int filterPos;

	setkey=entity->getKey() + Condition;
	from=Condition.Tokenize(_T(" "), tokenPos);
	if(from.CompareNoCase(_T("from"))==0) 
		from=Condition.Tokenize(_T(" "), tokenPos);

	with=Condition.Tokenize(_T(" "), tokenPos);
	filterPos=tokenPos;


	// Pool 에 존재하지 않으면
	if( EntitySetPool->Lookup(key, (CObject*&)entityList) == 0 )
	{
		entitySet = new CStringList();
		// Object의 Field를 정함
		entityList= (CStringList*)entity->getValue(from);
		
		pos=entityList->GetHeadPosition();	
		while(pos!=NULL)
		{
			FieldValue=entityList->GetNext(pos);
//			meta.setMetaFileName(FieldValue);

			tokenPos=filterPos;
			// include 일 경우
			if(with.IsEmpty()==true || with.CompareNoCase(_T("*")) == 0)
			{
				entitySet->AddTail(FieldValue);
			}
			else if(with.CompareNoCase(_T("include")) == 0)
			{
				filter=Condition.Tokenize(_T(" "), tokenPos);
				while (filter != "")
				{
//					if(filter.CompareNoCase(meta.getMetaFilter()) == 0)
					if(FieldValue.Find(filter) != -1)
					{
							entitySet->AddTail(FieldValue);
						break;
					}
					filter=Condition.Tokenize(_T(" "), tokenPos);
				}
			}
			// exclude일 경우
			else if(with.CompareNoCase(_T("exclude")) == 0)
			{
				filter=Condition.Tokenize(_T(" "), tokenPos);
				while (filter != "")
				{
					if(FieldValue.Find(filter) != -1)
					{
						break;
					}
					filter=Condition.Tokenize(_T(" "), tokenPos);
				}
				if(filter.IsEmpty() == true)
					entitySet->AddTail(FieldValue);
			}	

		}
		if(entitySet->IsEmpty() ==TRUE)
		{
			delete entitySet;
			entitySet=NULL;  // 함수 호출자는 NULL인지 체크해야 한다
		}
		else
		{
			EntitySetPool->SetAt(setkey, entitySet);
		}
	}
	return entitySet;
}
*/

/*
// (_T("DIR"), one of _T("dir / dir_pure / file"))
// 호출자는 return value 가 NULL인지 체크해야 한다
CStringList* EntityKit::getEntitySet(CString EntityName, CString condition)
{
	POSITION pos;
	Entity* entity;
	CString key;
	CString setkey;
	CStringList* entitySet; 

	setkey=EntityName+condition;

	// Pool 에 존재하지 않으면
	if( EntitySetPool->Lookup(key, (CObject*&)entitySet) == 0 )
	{

		entitySet= new CStringList();
		
		pos=entityCache->GetStartPosition();	
		while(pos!=NULL)
		{
			entityCache->GetNextAssoc(pos, key, (CObject*&)entity);
			if(EntityName.Compare(entity->getEntityName()) == 0)
			{
				if(condition.IsEmpty() == true)
				{
					// 모든 내용을 entitySet으로 반환

				}
				else
				{
					if(condition.Find(_T("dir_pure"))!=-1)
					{	
						CStringList* DirList;
						DirList=(CStringList*)entity->getValue(_T("dir"));
						DirList->RemoveHead();
						DirList->RemoveHead();
						entitySet->AddTail(DirList);
						
						
//						if( entity->getKey().Compare(_T("."))!=0 && entity->getKey().Compare(_T(".."))!=0 )
//						{
//							entitySet->AddTail( );
//						}

					}
					else
					{
						entitySet->AddTail((CStringList*)entity->getValue(condition));
					}

				}

			}

		}
		if(entitySet->IsEmpty() ==TRUE)
		{
			delete entitySet;
			entitySet=NULL;  // 함수 호출자는 NULL인지 체크해야 한다
		}
		else
		{
			EntitySetPool->SetAt(setkey, entitySet);
		}
	}
	return entitySet;
}

*/

/*
   EntitySet EntityKit::getEntitySet(CString entityName, Condition condition){
    EntitySet set = new EntitySet();
    return getEntitySet(set, entityName, condition);
  }

   EntitySet EntityKit::getEntitySet(CString entityName, Condition condition, CString orderByField, boolean ascend){
    EntitySet set = new OrderedEntitySet(orderByField, ascend);
    return getEntitySet(set, entityName, condition);
  }

   EntitySet EntityKit::getEntitySet(EntitySet set, CString entityName, Condition condition){
    Entity prototype = (Entity)entityPrototypes.get(entityName);
    if (prototype == NULL)
      return set;
    cache.Fetch(set, prototype, condition);
    EntitySet newSet = new EntitySet();
    Condition onlyNewEntityCondition = onlyNewEntityCondition(set, condition);
    persister->Fetch(newSet, prototype, onlyNewEntityCondition);
    newSet.setEntityKit(this);
    newSet.clearState();
    cache.put(newSet);
    set.addSet(newSet);
    return set;
  }

   Condition EntityKit::onlyNewEntityCondition(EntitySet exclusive, Condition condition) {
    Condition newCon = condition;
    exclusive.toFirst();
    while (exclusive.hasNext()) {
      Entity entity = (Entity)exclusive.nextEntity();
      newCon = new Condition(newCon, true, new Condition("entitykey", "<>", entity.getKey()));
    }
    return newCon;
  }
*/

	void EntityKit::Cache(Entity* entity)
	{

		entity->Save();
		entityCache->SetAt(entity->getKey(), (CObject*)entity);

/*
		CString ran;
		int rannum = rand();
	
		iran.Format((TCHAR)("%d",rannum));
		CTime t = CTime::GetCurrentTime();
		
		ran=t.Format( "%A%B%d%Y%H%M%S" );
		ran+=iran;
		entityCache->SetAt(ran, (CObject*)entity);
*/
	}
   void EntityKit::Insert(Entity* entity){
    persister->Insert(entity);
  }

   void EntityKit::Update(Entity* entity){
    persister->Update(entity);
  }

   void EntityKit::Delete(Entity* entity){
    persister->Delete(entity);
  }

/*
  static CString EntityKit::getKeyPrefix(CString key) {
    if (key == NULL)
      return NULL;
    if (key.indexOf("_") < 0)
      return "";
    return key.subCString(0, key.indexOf("_"));
  }

   void EntityKit::destroy() {

    entityPrototypes = NULL;
    persister = NULL;

  }

   void EntityKit::finalize() {
    destroy();
  }
*/

bool EntityKit::isValidFile(Entity* prototype, CString FileName)
{
	bool isDir;
	CString FileFilter;

	int tokenPos;
	CString tokenFileName;
	CString tokenFilter;


	CString fileFilter;
	UtilString::splitFileName(&FileName, &fileFilter);


	   // prototype에 설정한 확장자 filter가 "*" 이면 무조건 Tree에 추가하고
	   // prototype에 MainFrame에서 설정했으면, filtering을 통해 추가
	isDir= (prototype->getEntityName().Compare(_T("DIR"))==0) ? true : false;
	if(isDir)
	   FileFilter=prototype->getMetaInfo()->getMetaDirName();
	else
	   FileFilter=prototype->getMetaInfo()->getMetaFileName();

	   if(FileFilter.Compare(_T("*.*"))==0 || FileFilter.Compare(_T("*"))==0) return true;

   		tokenPos=0;
		tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);
		while (tokenFileName.IsEmpty()==false)
		{
			// if Directory인 경우
			if(isDir)
			{
				if(UtilString::isSubSet(tokenFileName, FileName) == true) return true;
			}
			// else File인 경우
			UtilString::splitFileName(&tokenFileName, &tokenFilter);

			   // case filter matching                                    // case *	                                // case may be directory
			if(tokenFilter.Compare(fileFilter)==0 || tokenFilter.CompareNoCase(_T("*")) == 0)
			{					
				if(UtilString::isSubSet(tokenFileName, FileName) == true) return true;
			}

			tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);

		}
	return false;

}

/*
bool EntityKit::isValidFile(Entity* prototype, CString FileName)
{	
	CString FileFilter;

	int tokenPos;
	CString tokenFileName;
	CString tokenFilter;
	MetaInfo tokenMeta;
	MetaInfo fileMeta;

	CString filenameFilter;

	   // prototype에 설정한 확장자 filter가 "*" 이면 무조건 Tree에 추가하고
	   // prototype에 MainFrame에서 설정했으면, filtering을 통해 추가
	if(prototype->getEntityName().Compare(_T("DIR"))==0)
	   FileFilter=prototype->getMetaInfo()->getMetaDirName();
	else
	   FileFilter=prototype->getMetaInfo()->getMetaFileName();

	   if(FileFilter.Compare(_T("*.*"))==0 || FileFilter.Compare(_T("*"))==0) return true;

	   		tokenPos=0;
			tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);
			while (tokenFileName.IsEmpty()==false)
			{
				tokenMeta.setMetaFileName(tokenFileName);
				tokenFilter=tokenMeta.getMetaFilter();
				
				fileMeta.setMetaFileName(FileName);
				filenameFilter=fileMeta.getMetaFilter();

				// file 과 filter의 형식이 다르면 무조건 false
				if(tokenFilter.IsEmpty() != filenameFilter.IsEmpty()) return false;

				   // case filter matching                                    // case *	                                // case may be directory
				if(tokenFilter.Compare(filenameFilter)==0 || tokenFilter.CompareNoCase(_T("*")) == 0 || tokenFilter.IsEmpty()==true)
				{
					
					int index;
					if(tokenFilter.IsEmpty()==false)
					{
					index=tokenFileName.ReverseFind(_T('.'));
					tokenFileName=tokenFileName.Left(index);
					}

					if(tokenFileName.Compare(_T("*"))==0)
					{
						return true;
					}
					tokenFileName.Remove(_T('*'));

					if(filenameFilter.IsEmpty()==false)
					{					
					index=FileName.ReverseFind(_T('.'));
					FileName=FileName.Left(index);
					}
					if(FileName.Find(tokenFileName)!=-1)
					{
						return true;
					}
				}

				tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);
	
		}
	return false;

}
*/