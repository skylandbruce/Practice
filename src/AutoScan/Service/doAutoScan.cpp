#include "StdAfx.h"
#include "doAutoScan.h"
#include "FilePersistence.h"


#include "FindFiles.h"
#include "FindTree.h"


#include "DIR.h"
#include "TEXTFILE.h"
#include "MIN.h"
#include "IncludeMIN.h"





doAutoScan::doAutoScan(void)
{
	init();
	initService();
}

doAutoScan::~doAutoScan(void)
{
}

void doAutoScan::init() {

	mBaseMeta=new MetaInfo();


/*
	DBConnectionManager dbMan;
	dbMan = new DBConnectionPool(YSGlobal.jdbcDriver, YSGlobal.dbUrl, YSGlobal.dbUser, YSGlobal.dbPwd);
*/	
  
/*
    Persistence p = new DBPersistence(dbMan);
  	p.setDatabase(YSGlobal.database);
*/
// Bruce : to next : 계층화 필요함
    p = new FilePersistence();
	

//    kit = new EntityKit(p, 30 * 60 * 1000);
    kit = new EntityKit(p);

#if 0 // clone instance
	kit->registerEntityPrototype(DIR::getPrototype());
	kit->registerEntityPrototype(MIN::getPrototype());
#else
	kit->registerEntityPrototype(new DIR());
	kit->registerEntityPrototype(new TEXTFILE());
	kit->registerEntityPrototype(new MIN());
	kit->registerEntityPrototype(new IncludeMIN());
#endif
 //   sharedObjects.put("kit", kit);
    
 //   sharedObjects.put("shelf", new Bookshelf(kit));
    
 //   TimeZone.setDefault(TimeZone.getTimeZone("JST"));

	Framework::init();
}

void doAutoScan::initService()
{
	registeService(_T("FindFiles"), new FindFiles());
	registeService(_T("FindTree"), new FindTree());

	Framework::initService();
}


// Root Path를 설정한다
bool doAutoScan::setRoot(void)
{	
	bool ret;

	CString BasePath=mBaseMeta->getMetaPath();
	CString RootPath;

//	BrowseFolder = new ViewFolderDialog();
	BrowseFolder = new ViewBrowseFolder();

	ret=BrowseFolder->Show();

	if(ret==true)
	{
		if(BasePath.IsEmpty()==true)
			return false;
			
		RootPath=BrowseFolder->getPath();
		RootInfo->setMetaPath(RootPath);
		RootInfo->setMetaRelativePath(BasePath);
	}
	delete BrowseFolder;
	return ret;
}

void doAutoScan::updateRoot(void)
{
	Framework::updateRoot();
}

MetaInfo* doAutoScan::getRootPath()
{
	if(setRoot()==true)
	{
		updateRoot();
		return RootInfo;		
	}
	return NULL;
}

// Makefile(*.mak) 의 위치를 지정한다
bool doAutoScan::setMakeFile(void)
{
	bool ret;
	BrowseFile = new ViewFileDialog();
//	BrowseFile = new ViewBrowseFile();
	ret=BrowseFile->Show();
	if(ret==true)
		mBaseMeta->setMetaFullPathName(BrowseFile->getPath());
	delete BrowseFile;
	
	return ret;	
}

void doAutoScan::updateMakeFile(void)
{
	
}

MetaInfo* doAutoScan::getMakeFile(void)
{
	if(setMakeFile()==true)
	{
		updateMakeFile();
		return mBaseMeta;		
	}
	return NULL;
}




void  doAutoScan::getTreeList()
{
	Entity* prototype;
	CString FileFilter;

	FindTree* tree;

	tree=(FindTree*)getService(_T("FindTree"));
	if(tree==NULL) return;

	prototype = kit->getPrototype(_T("TEXTFILE"));
	prototype->setProtoKey(_T("*.c *.C *.s *.S *.h *.H"));

	tree->getTree(prototype);
}

void  doAutoScan::openMIN(void)
{
	Entity* dirProto;
	POSITION dirPos;
	CMapStringToOb* DirSet;
	CString dirKey;
	CString DirName;
	DIR* dir;


	POSITION minpos;
	POSITION sourceCpos;
	POSITION sourceSpos;



	Entity* fileProto;
	POSITION filePos;
	CString fileKey;
	CMapStringToOb* FileSet;
	CString FileName;
	TEXTFILE* file;


	MIN* min;
	CString minPathName;
	CStringList* MINValueList;
	CString MinValue;
	CString MinSourceC;
	CString MinSourceS;

	dirProto=kit->getPrototype(_T("DIR"));
	dirProto->setProtoKey(_T("*")); // dir은 반드시 뒤에 \를 붙힌다
	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	DirSet=kit->getEntitySet(dirProto);
	if(DirSet->IsEmpty() == TRUE) 
	{
		delete DirSet;
		return;
	}


	dirPos=DirSet->GetStartPosition(); 
	while(dirPos!=NULL)
	{
		DirSet->GetNextAssoc(dirPos, dirKey, (CObject*&)dir);


		// getEntitySet() 이 Empty일 경우 메모리 해제 필수
		fileProto=kit->getPrototype(_T("TEXTFILE"));
		fileProto->setProtoKey(_T("*.c *.C *.s *.S")); // dir을 제외한 모든 file은 \없이 사용한다
		FileSet=kit->getEntitySet(fileProto, dir, _T("inpath"));
		if(FileSet->IsEmpty() == TRUE) 
		{
			delete FileSet;
			continue;
		}

		// MINfile을 만든다
		minPathName=dir->getEntityPath()+dir->getMetaInfo()->getMetaDirName()+_T(".")+_T("MIN");
		min=(MIN *)kit->getNewEntity(kit->getPrototype(_T("MIN")),minPathName);
		kit->Cache(min);
		
		DirName=dir->getMetaInfo()->getMetaDirName();
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



		filePos=FileSet->GetStartPosition(); 
		while(filePos!=NULL)
		{
			FileSet->GetNextAssoc(filePos, fileKey, (CObject*&)file);

			FileName=file->getMetaInfo()->getMetaFileName();
			// MIN의 C source 추가
			if( (file->getMetaInfo()->getMetaFilter()).CompareNoCase(_T("c"))==0 )
			{
				MinSourceC+=(_T("\t")+FileName+_T("\\\r\n"));

			}
			// MIN의 S source 추가
			else if( (file->getMetaInfo()->getMetaFilter()).CompareNoCase(_T("s")) ==0 )
			MinSourceS+=(_T("\t")+FileName+_T("\\\r\n"));
		}
		MINValueList->SetAt(sourceCpos, MinSourceC);
		MINValueList->SetAt(sourceSpos, MinSourceS);




			// 저장한다

	}


}

void  doAutoScan::saveMIN(Entity* prototype)
{
	
	CMapStringToOb* minSet;
	POSITION setPos;
	CString key;
	MIN* min;
	Entity* minProto;

	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	minProto=kit->getPrototype(_T("MIN"));
	minProto->setProtoKey(_T("*.*"));
	minSet=kit->getEntitySet(minProto);
	if(minSet->IsEmpty()==TRUE)
	{
		delete minSet;
		return;
	}

		setPos=minSet->GetStartPosition(); 
		while(setPos!=NULL)
		{
			minSet->GetNextAssoc(setPos, key, (CObject*&)min);
			p->Update(min);
		}

}

void doAutoScan::openIncludeMIN()
{
	IncludeMIN* min;
	CString minPathName;
	CStringList* valueList;
	CStringList* pathsList;
	CStringList* allpathsList;



	Entity* fileProto;
	TEXTFILE* file;
	CString fileName;
	CString dirName;

	CMapStringToOb* FileSet;
	POSITION setpos;
	CString key;

	CString relativePath;

// dir 중복 제거를 위한 검색을 위해
	CMapStringToOb* dirSet; 
	dirSet=new CMapStringToOb();
	LPCTSTR rkey;





	minPathName=mBaseMeta->getMetaPath()+_T("IncludeMin.MIN");
	min=(IncludeMIN *)kit->getNewEntity(kit->getPrototype(_T("IncludeMIN")),minPathName);
	kit->Cache(min);
				
	valueList=(CStringList*)min->getValue(_T("root"));
	valueList->AddTail(RootInfo->getMetaRelativePath().TrimRight(_T("\\")));
	min->setValue(_T("root"),valueList);

	pathsList=(CStringList*)min->getValue(_T("paths"));
	allpathsList=(CStringList*)min->getValue(_T("allpaths"));

	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다

	fileProto=kit->getPrototype(_T("TEXTFILE"));
	fileProto->setProtoKey(_T("*.h *.H")); // dir은 반드시 뒤에 \를 붙힌다
	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	FileSet=kit->getEntitySet(fileProto);
	if(FileSet->IsEmpty() == TRUE) 
	{
		delete FileSet;
		return;
	}


		 int dirCount=1;
		setpos=FileSet->GetStartPosition(); 
		while(setpos!=NULL)
		{
			FileSet->GetNextAssoc(setpos, key, (CObject*&)file);

			if( dirSet->LookupKey(file->getMetaInfo()->getMetaRelativePath(), rkey) == TRUE)
				continue;

				dirSet->SetAt(file->getMetaInfo()->getMetaRelativePath(), NULL);

				dirName=file->getMetaInfo()->getMetaDirName().MakeUpper();
				relativePath=file->getMetaInfo()->getMetaRelativePath();
				relativePath.TrimRight(_T("\\"));
				relativePath.Replace(_T("."), _T("$(SRCROOT)"));
				relativePath.Replace(_T("\\"),_T("/"));
				
				
				pathsList->AddTail(dirName+_T("=\t")+relativePath+_T("\r\n"));

				 allpathsList->AddTail(_T(" $(")+dirName+_T(") "));		
				if(dirCount%10==0)
					allpathsList->AddTail(_T("\\\r\n\t"));

				 dirCount++;

		}
		min->setValue(_T("paths"), pathsList);
		min->setValue(_T("allpaths"), allpathsList);
	


}

void  doAutoScan::saveIncludeMIN(Entity* prototype)
{
	CStringList* fieldOrder=new CStringList();	

	CMapStringToOb* minSet;
	POSITION setPos;
	CString key;
	IncludeMIN* min;
	Entity* minProto;

	fieldOrder->AddTail(_T("header"));
	fieldOrder->AddTail(_T("root"));
	fieldOrder->AddTail(_T("paths"));
	fieldOrder->AddTail(_T("allpaths"));
	fieldOrder->AddTail(_T("incprefix"));
	fieldOrder->AddTail(_T("allincludes"));

	// 반드시 NULL(Pool에도 없고, 질의 결과에도 없음) 인지 체크해야 한다
	minSet=kit->getEntitySet(prototype);

	minProto=kit->getPrototype(_T("IncludeMIN"));
	minProto->setProtoKey(_T("*.*")); // dir은 반드시 뒤에 \를 붙힌다
	minSet=kit->getEntitySet(minProto);
	if(minSet->IsEmpty() == TRUE) 
	{
		delete minSet;
		return;
	}


		setPos=minSet->GetStartPosition(); 
		while(setPos!=NULL)
		{
			minSet->GetNextAssoc(setPos, key, (CObject*&)min);
			p->Update(min, fieldOrder);
//			p->Update(min);
		}

}

void doAutoScan::createConfigure()
{
	openMIN();
	openIncludeMIN();

	saveMIN(kit->getPrototype(_T("MIN")));
	saveIncludeMIN(kit->getPrototype(_T("IncludeMIN")));

	AfxMessageBox(_T("Comfile 환경이 준비되었습니다!        "));	

}