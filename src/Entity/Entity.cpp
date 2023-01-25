#include "StdAfx.h"
#include "Entity.h"

Entity::Entity(void)
{
    fieldValues = new CMapStringToOb();
    state = STATE_NEW;
}

Entity::~Entity(void)
{
	POSITION pos;
	CObject* object;
	CString key;

//	pos=fieldValues->GetStartPosition();	
//	while(pos!=NULL)
//	{
//		fieldValues->GetNextAssoc(pos, key, (CObject*&)object);
//		delete object;
//	}

	delete fieldValues;

}

CString Entity::getEntityName() {
	MetaInfo* metaInfo;
	metaInfo=getMetaInfo();
	if(metaInfo!=NULL)
		return metaInfo->getMetaObjName();
return _T("");
}

void Entity::setEntityPath(CString FullPathName)
{
	CString EntityName;
	MetaInfo* metaInfo;
	
	EntityName=getEntityName();		
	if(EntityName.IsEmpty()!=true)
	{
		metaInfo=getMetaInfo();
		if(EntityName.Compare(_T("DIR"))==0)
			metaInfo->setMetaPath(FullPathName);
		else
			metaInfo->setMetaFullPathName(FullPathName);
	}
}

CString Entity::getEntityPath()
{
	CString EntityName;
	MetaInfo* metaInfo;
	
	EntityName=getEntityName();		
	if(EntityName.IsEmpty()!=true)
	{
		metaInfo=getMetaInfo();
		if(EntityName.Compare(_T("DIR"))==0)
			return metaInfo->getMetaPath();
		else
			return metaInfo->getMetaFullPathName();
	}
	return _T("");
}

/*
void Entity:: setEntityKit(EntityKit* kit) {
this->kit = kit;
}
*/

bool Entity::isDirectory(CString key)
{
	CString Ending;
	Ending=key.Right(1);
	if(Ending.Compare(_T("\\"))==0)
		return true;
	return false;
}


void Entity::setKey(CString key) {
	this->key = key;
	if(isDirectory(key))
		getMetaInfo()->setMetaPath(key);
	else
		getMetaInfo()->setMetaFullPathName(key);
	
}

void Entity::setProtoKey(CString key)
{
	if(this->getEntityName().Compare(_T("DIR"))==0)
		setKey(this->getEntityName()+_T("\\")+key+_T("\\"));
	else
		setKey(this->getEntityName()+_T("\\")+key);
}


CString Entity::getKey() {
return key;
}

void Entity:: clearState() {
state = STATE_CLEARED;
}

void Entity:: Delete()  {
if (state == STATE_NEW)
  state = STATE_INVALID;
else
  state = STATE_DELETED;
  Save();
}

void Entity:: Update() {
if (state == STATE_CLEARED)
  state = STATE_UPDATED;
}


void Entity:: Save()  
{
	if (state == STATE_NEW) {
//	  kit->Insert(this);
	  state = STATE_CLEARED;
	}
	else if (state == STATE_UPDATED) {
//	  kit->Update(this);
	  state = STATE_CLEARED;
	}
	else if (state == STATE_DELETED) {
//	  kit->Delete(this);
	  state = STATE_INVALID;
	}
}

int Entity::getState()
{
	return state;
}



void Entity::registerField(CString fieldName, CObject* initValue) {
	fieldValues->SetAt(fieldName, initValue);
}

CObject* Entity::getValue(CString fieldName) {
	CObject *value;
	fieldValues->Lookup(fieldName, (CObject*&)value); 
	return value;
}

void Entity:: setValue(CString fieldName, CObject* value) {
//	CObject *oldValue;
//if (fieldValues->Lookup(fieldName,(CObject*&)oldValue)==0) return;
//	delete oldValue;
	fieldValues->SetAt(fieldName, value);
	Update();
}

boolean Entity::equals(CObject* other) {
/*
	int ret=false;
	if (other == NULL)
	return false;

	if (other->IsKindOf(RUNTIME_CLASS(Entity)) {
	ret=key.Compare(((Entity*)other)->getKey());
	}

	if(ret==0) return true;
	return false;
*/
	return TRUE;
}

CMapStringToOb* Entity::getValueTable() {
	return fieldValues;
}


Entity* Entity::getInstance()
{
	return NULL;
}
MetaInfo* Entity::getMetaInfo()
{
	return NULL;
}
