#pragma once
#include "MetaInfo.h"

#define STATE_NEW  1
#define STATE_CLEARED  2
#define STATE_UPDATED  3
#define STATE_DELETED  4
#define STATE_INVALID  -1


class Entity
{
protected:


  static const int MT_DEFAULT = 0;
  static const int MT_INTEGER = 1;
  static const int MT_DOUBLE = 2;
  static const int MT_CString = 3;
  static const int MT_DATE = 4;
  static const int MT_TIME = 5;
  static const int MT_TIMESTAMP = 6;

  int state;
  CMapStringToOb* fieldValues;
//  EntityKit* kit;
  CString key;

public:
	Entity(void);
	~Entity(void);

	// Overriding ÇÔ¼ö
//////////////////////////////////////////////////////////////////
	virtual  Entity* getInstance();
	virtual  MetaInfo* getMetaInfo();

//////////////////////////////////////////////////////////////////

	CString getEntityName(void); 
	void setEntityPath(CString FullPathName);
	CString getEntityPath(void);
//	void  setEntityKit(EntityKit* kit) ;

	bool isDirectory(CString key);
	void  setKey(CString key) ;
	void  setProtoKey(CString key);
	CString getKey() ;

	void  clearState() ;
	void  Delete()  ;
	void  Update() ;
	void  Save()  ;
	int getState();

	void  registerField(CString fieldName, CObject* initValue) ;
	CObject* getValue(CString fieldName) ;
	void  setValue(CString fieldName, CObject* value) ;
	boolean equals(CObject* other) ;
	CMapStringToOb* getValueTable() ;

};
