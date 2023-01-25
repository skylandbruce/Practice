#include "StdAfx.h"
#include "FilePersistence.h"

FilePersistence::FilePersistence(void)
{

}

FilePersistence::~FilePersistence(void)
{
}


BOOL FilePersistence::OpenFile(CString FileName, CString Mode)
{
	BOOL ret;
	if(Mode.Compare(_T("write"))==0)
	{
		ret=File.Open(FileName, CFile::modeCreate|CFile::modeWrite, &e);
	}
	else if(Mode.Compare(_T("read"))==0)
	{
		ret=File.Open(FileName, CFile::modeRead, &e);
	}
	if(!ret)
	{

		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
	}
	return ret;
}


Entity* FilePersistence::fetchEntity(Entity* entity, CString key)
{
	return entity;
}
/*
void Fetch(EntitySet set, Entity* prototype, Condition condition)
{

}
*/

void FilePersistence::Fetch(Entity* entity)
{

}

void FilePersistence::Insert(Entity* entity)
{
	CMapStringToOb* valueTable;
	POSITION tablePos;
	CString key;

	CStringList* valueList;
	POSITION valuePos;

	CString value;

	if (!File.Open(entity->getMetaInfo()->getMetaFullPathName(), CFile::modeWrite, &e))
	{
		// complain if an error happened
		// no need to delete the e object

		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return;
	}
	else
	{
		File.SeekToEnd();

		valueTable=entity->getValueTable();
		tablePos=valueTable->GetStartPosition();

		while( tablePos!=NULL )
		{
			valueTable->GetNextAssoc(tablePos, key, (CObject*&)valueList);

			valuePos=valueList->GetHeadPosition();
			while( valuePos!=NULL )
			{
				value=valueList->GetNext(valuePos);
				File.Write(value, value.GetLength());
			}

		}
		File.Close();

	}
}


  

void FilePersistence::Update(Entity* entity)
{

	CMapStringToOb* valueTable;
	POSITION tablePos;
	CString key;

	CStringList* valueList;
	POSITION valuePos;

	CString value;
//	CString str(_T("abc테스트123\r\n"));
		
	

	if (!File.Open(entity->getMetaInfo()->getMetaFullPathName(), CFile::modeCreate|CFile::modeWrite, &e))
    {
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return;
    }
	File.SeekToBegin();

	CArchive ar( &File, CArchive::store );

	valueTable=entity->getValueTable();
	tablePos=valueTable->GetStartPosition();

	while( tablePos!=NULL )
	{
		valueTable->GetNextAssoc(tablePos, key, (CObject*&)valueList);

		valuePos=valueList->GetHeadPosition();
		while( valuePos!=NULL )
		{
			value=valueList->GetNext(valuePos);
			value.OemToCharA();

//			File.Write(value, value.GetLength()*sizeof(TCHAR));
			ar.WriteString(value);
//			ar<<value;

		}
	}



	ar.Close();
	File.Close();

}

void FilePersistence::Update(Entity* entity, CStringList* fieldOrder)
{
	CString fieldName;


	CStringList* valueList;
	POSITION valuePos;

	CString value;
//	CString str(_T("abc테스트123\r\n"));
		
	POSITION orderPos;	

	if (!File.Open(entity->getMetaInfo()->getMetaFullPathName(), CFile::modeCreate|CFile::modeWrite, &e))
    {
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return;
    }
	File.SeekToBegin();

	CArchive ar( &File, CArchive::store );

	orderPos=fieldOrder->GetHeadPosition();
	while( orderPos!=NULL )
	{
		fieldName=fieldOrder->GetNext(orderPos);
	
		valueList=(CStringList*)entity->getValue(fieldName);

		valuePos=valueList->GetHeadPosition();
		while( valuePos!=NULL )
		{
			value=valueList->GetNext(valuePos);
			value.OemToCharA();

	//			File.Write(value, value.GetLength()*sizeof(TCHAR));
			ar.WriteString(value);
	//			ar<<value;

		}

	}


	ar.Close();
	File.Close();

}

void FilePersistence::Delete(Entity* entity)
{

}

void FilePersistence::Rename(Entity* entity)
{
//	if(OpenFile(entity->getMetaInfo()->getMetaFullPathName(),_T("read"))==true)
		File.Rename(entity->getMetaInfo()->getMetaFullPathName(), entity->getMetaInfo()->getMetaPath()+entity->getMetaInfo()->getMetaFileName());

}