#include "StdAfx.h"
#include "doReName.h"
#include "FilePersistence.h"

#include "FindFiles.h"
#include "FindTree.h"

#include "DIR.h"
#include "TEXTFILE.h"

doReName::doReName(void)
{
	BrowseFolder=NULL;
	init();
	initService();
}

doReName::~doReName(void)
{
}

void doReName::init() {

    p = new FilePersistence();
//    kit = new EntityKit(p, 30 * 60 * 1000);
    kit = new EntityKit(p);

	kit->registerEntityPrototype(new DIR());
	kit->registerEntityPrototype(new TEXTFILE());

	Framework::init();
}

void doReName::initService()
{
	registeService(_T("FindFiles"), new FindFiles());
	registeService(_T("FindTree"), new FindTree());

	Framework::initService();
}


// Root Path를 설정한다
bool doReName::setRoot(void)
{	
	bool ret=false;
	if(BrowseFolder==NULL)
		BrowseFolder = new ViewBrowseFolder();

	if(BrowseFolder->Show() == true)
	{
		RootPath=BrowseFolder->getPath();
		ret=true;
	}
	if(RootPath.IsEmpty() == false)
	{
		delete BrowseFolder;
		BrowseFolder=NULL;
	}
	return ret;
}

void doReName::updateRoot(void)
{
	RootInfo->setMetaPath(RootPath);
	// tree에서 인식할 확장자만 filtering
	RootInfo->setMetaFilter(_T("*"));

	Framework::updateRoot();

}

MetaInfo* doReName::getRootPath()
{
	if(setRoot()==true)
	{
		updateRoot();
		return RootInfo;		
	}
	return NULL;
}

void doReName::setFileName(CString fileName)
{
	DIR* dir;
	dir=(DIR*)kit->getPrototype(_T("TEXTFILE"));
	
	dir->setKey(_T("\\")+dir->getEntityName()+_T("\\")+fileName);
//	dir->getMetaInfo()->setMetaFileName(fileName);
}

void doReName::setDirName(CString dirName)
{
	DIR* dir;
	dir=(DIR*)kit->getPrototype(_T("DIR"));

	dir->setKey(dir->getEntityName()+_T("\\")+dirName+_T("\\"));
//	dir->getMetaInfo()->setMetaDirName(dirName);
//	dir->getMetaInfo()->setMetaFileName(_T(""));
}

void  doReName::getTreeList()
{
	FindTree* tree;
	tree=(FindTree*)getService(_T("FindTree"));
	if(tree==NULL) return;

	
	tree->getTree(kit->getPrototype(_T("TEXTFILE")));
}

/*
void  doReName::getTreeList(CString filter)
{
	FindTree* tree;
	tree=(FindTree*)getService(_T("FindTree"));
	if(tree==NULL) return;
	
	RootInfo->setMetaFilter(filter);
	tree->getTree(kit->getPrototype(_T("TEXTFILE")));
}
*

void  doReName::openReName(void)
{
/*



	CMapStringToOb* DirSet;
	POSITION setpos;
	CString key;
	DIR* dir;

	CStringList* FileList;
	POSITION filepos;
	CString DirName;
	CString FileName;



	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	DirSet=kit->getEntitySet(_T("DIR"));

	if(DirSet!=NULL)
	 {
		setpos=DirSet->GetStartPosition(); 
		while(setpos!=NULL)
		{
			DirSet->GetNextAssoc(setpos, key, (CObject*&)dir);

			// getEntitySet 은 반드시 NULL 체크해야 한다
			// filename 에 대한 검색 문자열 filtering
			FileList=kit->getEntitySet((Entity*)dir, _T("from file include .c .C .s .S"));
			if(FileList != NULL)
			{
				// MINfile을 만든다
				min=(MIN *)kit->getNewEntity(_T("MIN"),dir->getMetaInfo()->getMetaPath());
				min->setEntityPath(dir->getEntityPath()+dir->getMetaInfo()->getMetaDirName()+_T(".")+min->getEntityName());
				
				DirName=min->getMetaInfo()->getMetaDirName();
				// AUTODIR 의 일괄변경
				MINValueList=(CStringList*)min->getValue(_T("format"));
				for(int index=0; index < MINValueList->GetCount(); index++)
				{
					minpos=MINValueList->FindIndex(index);
					MinValue=MINValueList->GetAt(minpos);
					DirName.MakeUpper();
					MinValue.Replace(_T("AUTODIR"), DirName );
					MINValueList->SetAt( minpos, MinValue);
				}
		
				sourceCpos=MINValueList->FindIndex(0);
				MinSourceC=MINValueList->GetAt(sourceCpos); //srcc
				sourceSpos=MINValueList->FindIndex(1);
				MinSourceS=MINValueList->GetAt(sourceSpos); //srcs

				// 해당 디렉토리의 File 목록으로 MIN file을 채운다
//				FileList=(CStringList*)dir->getValue(_T("file"));
				filepos=FileList->GetHeadPosition();
				MetaInfo metaInfo;
				while(filepos!=NULL)
				{
					FileName=FileList->GetNext(filepos);
					metaInfo.setMetaFileName(FileName);

					// MIN의 C source 추가
					if( (metaInfo.getMetaFilter()).CompareNoCase(_T("c"))==0 )
					{
						MinSourceC+=(_T("\t")+FileName+_T("\\\r\n"));

					}
					// MIN의 S source 추가
					else if( (metaInfo.getMetaFilter()).CompareNoCase(_T("s")) ==0 )
					MinSourceS+=(_T("\t")+FileName+_T("\\\r\n"));
				}
				MINValueList->SetAt(sourceCpos, MinSourceC);
				MINValueList->SetAt(sourceSpos, MinSourceS);




				// 저장한다

			}
		}
	 }	

}
*/


void  doReName::saveReName(CString objName)
{
/*	
	CMapStringToOb* minSet;
	POSITION setPos;
	CString key;
	MIN* min;
	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	minSet=kit->getEntitySet(objName);

	if(minSet->IsEmpty()==false || minSet!=NULL)
	 {
		setPos=minSet->GetStartPosition(); 
		while(setPos!=NULL)
		{
			minSet->GetNextAssoc(setPos, key, (CObject*&)min);
			p->Update(min);
		}
	}
*/
}


void doReName::doConfigure(CString from, CString withFileName, CString toFileName, CString Case, BOOL extOnly)
{
	CMapStringToOb* resultSet;

	POSITION setPos;
	CString key;
	Entity* entity;

	CString fileName;
	CString filterName;

	if(from.Compare(_T("file"))==0)
		resultSet=kit->getEntitySet(kit->getPrototype(_T("TEXTFILE")));
	else
		resultSet=kit->getEntitySet(kit->getPrototype(_T("DIR")));
		
	if(resultSet->IsEmpty()==TRUE)
	{
		delete resultSet;
		return;
	}

	setPos=resultSet->GetStartPosition(); 
	while(setPos!=NULL)
	{
		resultSet->GetNextAssoc(setPos, key, (CObject*&)entity);

		// resultSet 의 file들을 모두 Rename한다
		if(from.Compare(_T("file"))==0)
		{
			if(extOnly==TRUE)
			{	
				filterName=entity->getMetaInfo()->getMetaFilter();
			}
				fileName=entity->getMetaInfo()->getMetaFileName();
		}
		else if(from.Compare(_T("dir"))==0)
		{
			fileName=entity->getMetaInfo()->getMetaDirName();
		}

		// Rename 한다
		UtilString::replaceSet(withFileName, toFileName, &fileName);	

		// case 설정
		if(Case.Compare(_T("upcase"))==0)
		{
			if(extOnly==TRUE) 
				filterName.MakeUpper();
			else
				fileName.MakeUpper();

		}
		else if(Case.Compare(_T("locase"))==0)
		{
			if(extOnly==TRUE) 
				filterName.MakeLower();
			else
				fileName.MakeLower();
		}

		if(extOnly==TRUE)
		{
			fileName.Replace(entity->getMetaInfo()->getMetaFilter(), filterName);
		}

		// 최종 fileName을 저장한다
		entity->getMetaInfo()->setMetaFileName(fileName);

	}


}

void doReName::doAction(CString from)
{
	CMapStringToOb* resultSet;

	POSITION setPos;
	CString key;
	Entity* entity;

	if(from.Compare(_T("file"))==0)
	{
		resultSet=kit->getEntitySet(kit->getPrototype(_T("TEXTFILE")));
	}
	else
	{
		resultSet=kit->getEntitySet(kit->getPrototype(_T("DIR")));
	}

	setPos=resultSet->GetStartPosition(); 
	while(setPos!=NULL)
	{
		resultSet->GetNextAssoc(setPos, key, (CObject*&)entity);
		p->Rename(entity);
	}


	AfxMessageBox(_T("변경이 완료 되었습니다!        "));	

}