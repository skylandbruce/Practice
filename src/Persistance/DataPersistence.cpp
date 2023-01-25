#include "StdAfx.h"
#include "DataPersistence.h"

DataPersistence::DataPersistence(void)
{

}

DataPersistence::~DataPersistence(void)
{
}


BOOL DataPersistence::OpenFile(CString FileName, CString Mode)
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


Entity* DataPersistence::fetchEntity(Entity* entity, CString key)
{
	return entity;
}
/*
void Fetch(EntitySet set, Entity* prototype, Condition condition)
{

}
*/

void DataPersistence::Fetch(Entity* entity)
{

}

int DataPersistence::FetchSet(CPtrArray* setArray, CString fileName)
{

	CMapStringToOb* valueTable;
	POSITION tablePos;
	CString key;

	Entity* entity;
	CString* value;
	CString metaValue;

	int savedCount=0;
//	CString str(_T("abc테스트123\r\n"));
		
	

	if (!File.Open(fileName, CFile::modeRead, &e))
    {
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return 0;
    }
	File.SeekToBegin();

	CArchive ar( &File, CArchive::load );

	ar>>savedCount;

	if(setArray!=NULL)
	{
	//	ar.WriteClass(setArray);


		for(int count=0; count<savedCount; count++)
		{
			entity=(Entity*)(*setArray)[count];

	//		ar.WriteClass(entity);
			
			ar>>metaValue;
			entity->getMetaInfo()->setMetaFullPathName(metaValue);
			valueTable=entity->getValueTable();
			tablePos=valueTable->GetStartPosition();

			while( tablePos!=NULL )
			{
				valueTable->GetNextAssoc(tablePos, key, (CObject*&)value);
				ar>>(*value);
			}
			entity->Save();

		}
	}//if
	ar.Close();
	File.Close();


	return savedCount;
}


void DataPersistence::Insert(Entity* entity)
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


  

void DataPersistence::Update(Entity* entity)
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

void DataPersistence::Update(Entity* entity, CStringList* fieldOrder)
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


void DataPersistence::UpdateSet(CPtrArray* setArray, CString fileName)
{

	CMapStringToOb* valueTable;
	POSITION tablePos;
	CString key;

	Entity* entity;
	CString* value;
//	CString str(_T("abc테스트123\r\n"));
		
	

	if (!File.Open(fileName, CFile::modeCreate|CFile::modeWrite, &e))
    {
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return;
    }
	File.SeekToBegin();

	CArchive ar( &File, CArchive::store );

	ar<<(setArray->GetCount());

//	ar.WriteClass(setArray);

	for(int count=0; count<setArray->GetCount(); count++)
	{
		entity=(Entity*)(*setArray)[count];

//		ar.WriteClass(entity);

		ar<<(entity->getMetaInfo()->getMetaFullPathName());
		valueTable=entity->getValueTable();
		tablePos=valueTable->GetStartPosition();

		while( tablePos!=NULL )
		{
			valueTable->GetNextAssoc(tablePos, key, (CObject*&)value);
				ar<<(*value);
		}

	}

	ar.Close();
	File.Close();

}



void DataPersistence::Delete(Entity* entity)
{

}

void DataPersistence::Rename(Entity* entity)
{

}