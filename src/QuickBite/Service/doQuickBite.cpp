#include "StdAfx.h"
#include "doQuickBite.h"
#include "DataPersistence.h"

#include "EXEFILE.h"

doQuickBite::doQuickBite(void)
{
	init();
	initService();
}

doQuickBite::~doQuickBite(void)
{
//	if(isBasic==false)
//		doBasic();
//	p->UpdateSet(EntitySet, DataPathFile+_T("\\")+DATAFILE);
}

void doQuickBite::init() {

    p = new DataPersistence();

    kit = new EntityKit(p);

	kit->registerEntityPrototype(new EXEFILE());

	Framework::init();
}

void doQuickBite::initService()
{

	Framework::initService();
}


// 실행 File를 설정한다
/*
bool doQuickBite::setExeFile(void)
{	
	bool ret=false;
	BrowseFile = new ViewFileDialog();

	if(BrowseFile->Show() == true)
	{
		ExeFilePath=BrowseFile->getPath();
		ret=true;
	}

	delete BrowseFile;

	return ret;
}
*/

Entity* doQuickBite::getExeFile(int index)
{
	Entity* entity;
	CString Key;
	CString* strTitle=new CString(_T("실행버튼"));

		Key.Format(_T("%d"), index);
		entity=kit->getNewEntity(kit->getPrototype(_T("EXEFILE")), Key);
		entity->getMetaInfo()->setMetaFullPathName(_T(""));
		entity->setValue(_T("title"), (CObject*)strTitle);
		kit->Cache(entity);
		return entity;
}

ViewBitmapButton* doQuickBite::getBitmapButton(Entity* entity, int index)
{
	ViewBitmapButton *bitmapButton;
	entity=(Entity*)(*EntitySet)[index];

	bitmapButton=new ViewBitmapButton();
	bitmapButton->setExeFile(entity); 
	buttonArray.Add(bitmapButton);	
	return bitmapButton;
}



void doQuickBite::updateRoot(CString path)
{
	RootInfo->setMetaPath(path);
	Framework::updateRoot();
}

MetaInfo* doQuickBite::getRootPath()
{
	CString strPath;
	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);

	strPath=CString(path);

	updateRoot(strPath);
	return RootInfo;		
}

#define MAX_BUTTON 10
void doQuickBite::doConfigure(CWnd* pParentWnd)
{
	TCHAR path[MAX_PATH];	

	ViewBitmapButton* bitmapButton;
	Entity* entity;
	CString* Title;
	validButtonCount=0; // Persistence에서 얻어 초기화 한다

	isBasic=true;


	GetCurrentDirectory(MAX_PATH, path);
	DataPathFile=CString(path);

	validButtonCount = p->FetchSet(NULL, DataPathFile+_T("\\")+DATAFILE);

	getExeFile(0);
	for(int index=1; index<validButtonCount && index<MAX_BUTTON; index++)
	{
		getExeFile(index);
	}
	EntitySet=kit->getArrayEntitySet(kit->getPrototype(_T("EXEFILE")));
	
	if(validButtonCount>0)
		p->FetchSet(EntitySet, DataPathFile+_T("\\")+DATAFILE);

	entity=(Entity*)(*EntitySet)[0];
	Title=(CString*)(entity->getValue(_T("title")));
	bitmapButton=getBitmapButton(entity, 0);
	bitmapButton->Create(pParentWnd, 0);
	bitmapButton->SetWindowTextA(*Title);// Create되고 나서 지정 가능

}

void doQuickBite::doAction()
{
	
}


void doQuickBite::doExtend(CWnd* pParentWnd)
{
	ViewBitmapButton* bitmapButton;
	Entity* entity;
	CString* Title;
//	CString Key;
	RECT Rect;

	pParentWnd->GetWindowRect(&Rect);
	if(isBasic==true)
	{
		pParentWnd->SetWindowPos(NULL,Rect.left,Rect.top,FRAME_WIDTH,FRAME_HEIGHT+BUTTON_HEIGHT*(EntitySet->GetCount()-1), SWP_DRAWFRAME);

		for(int index=1; index<EntitySet->GetCount() && index<MAX_BUTTON; index++)
		{
			//Key.Format(_T("%d"), index);
			//entity=kit->getEntity(Key);
			entity=(Entity*)(*EntitySet)[index];
			Title=(CString*)(entity->getValue(_T("title")));
		
			bitmapButton=getBitmapButton(entity, index);
			bitmapButton->Create(pParentWnd, index);
			bitmapButton->SetWindowTextA(*Title); // Create되고 나서 지정 가능
		}
		isBasic=false;
	}
	else
	{
		doBasic();
		pParentWnd->SetWindowPos(NULL,Rect.left,Rect.top,FRAME_WIDTH,FRAME_HEIGHT, SWP_DRAWFRAME);
		isBasic=true;
	}
}

void doQuickBite::doBasic()
{
	ViewBitmapButton *bitmapButton;
	Entity* entity;
	bool needUpdate=false;

	int Count=EntitySet->GetCount();
	int removedCount=0;
	
	entity=(Entity*)(*EntitySet)[0];
	if(entity->getState()!=STATE_CLEARED)
	{
		needUpdate=true;
		entity->Save();
	}

	for(int index=1; index<Count && index<MAX_BUTTON; index++)
	{
		bitmapButton=(ViewBitmapButton*)buttonArray[index];
		bitmapButton->DestroyWindow();
		delete bitmapButton;
		
		entity=(Entity*)(*EntitySet)[index-removedCount];
		if(entity->getMetaInfo()->getMetaFullPathName().IsEmpty() == true || ((CString*)(entity->getValue(_T("title"))))->IsEmpty() == true)
		{
			EntitySet->RemoveAt(index-removedCount,1);
			removedCount++;
		}
		else
		{
			if(entity->getState()!=STATE_CLEARED)
			{
				needUpdate=true;
				entity->Save();
			}
		}
	}
	
	buttonArray.RemoveAt(1,Count-1);

// save
	if(validButtonCount < EntitySet->GetCount() || needUpdate==true || removedCount>0)
	{
		validButtonCount=EntitySet->GetCount();
		p->UpdateSet(EntitySet, DataPathFile+_T("\\")+DATAFILE);
	}
}

void doQuickBite::addNewButton(CWnd* pParentWnd)
{
	RECT Rect;
	int Count=EntitySet->GetCount();

	ViewBitmapButton* bitmapButton;
	Entity* entity;

	if(Count<MAX_BUTTON)
	{
		pParentWnd->GetWindowRect(&Rect);

		entity=getExeFile(Count);		
		EntitySet->Add(entity);
		
		if(isBasic==true)
			doExtend(pParentWnd);
		else
		{
			bitmapButton=getBitmapButton(entity, Count);
			bitmapButton->Create(pParentWnd, Count);
			pParentWnd->SetWindowPos(NULL,Rect.left,Rect.top,FRAME_WIDTH,FRAME_HEIGHT+BUTTON_HEIGHT*(EntitySet->GetCount()-1), SWP_DRAWFRAME);
		}
	}
}