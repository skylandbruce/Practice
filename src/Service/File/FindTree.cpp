#include "StdAfx.h"
#include "FindTree.h"


FindTree::FindTree(void)
{
}

FindTree::~FindTree(void)
{
}

// RootPath와 filter는 ViewBrowseFolder 을 통해 설정된다
// Deplecated
/*
void FindTree::getTree()
{	
	mFindFiles=(FindFiles*)getService(_T("FindFiles"));
	recursiveTree(RootPath, RootInfo->getMetaFilter());
}
*/

void FindTree::getTree(Entity* prototype)
{	
	mFindFiles=(FindFiles*)getService(_T("FindFiles"));
	recursiveTree(RootPath, prototype);
}

/*
void FindTree::recursiveTree(CString path, CString filter)
{
	CStringList* list;
	CString str;
	CString subpath;
	POSITION pos;
	
	list=mFindFiles->getPathList(path, filter);
	if(list==NULL || list->GetCount()==2) return;

	if(list->IsEmpty()==false)
	{
		pos=list->GetHeadPosition();
			str=list->GetNext(pos);	//.
			str=list->GetNext(pos); //..
		while(pos!=NULL)
		{
			str=list->GetNext(pos);
			subpath=path+str+_T("\\");
			recursiveTree(subpath, filter);
		}
	}
	return;
}
*/

/*
void FindTree::recursiveTree(CString path, Entity* prototype)
{
	CStringList* list;
	CString str;
	CString subpath;
	POSITION pos;
	
	list=mFindFiles->getPathList(path, prototype);
	if(list==NULL || list->GetCount()==2) return;

	if(list->IsEmpty()==false)
	{
		pos=list->GetHeadPosition();
			str=list->GetNext(pos);	//.
			str=list->GetNext(pos); //..
		while(pos!=NULL)
		{
			str=list->GetNext(pos);
			subpath=path+str+_T("\\");
			recursiveTree(subpath, prototype);
		}
	}
	return;
}
*/

void FindTree::recursiveTree(CString path, Entity* prototype)
{
	CStringList* dirList;
	CString str;
	CString subpath;
	POSITION pos;
	
	dirList=mFindFiles->getDirList(path, prototype);
	if(dirList==NULL || dirList->GetCount()==2) return;

	if(dirList->IsEmpty()==false)
	{
		pos=dirList->GetHeadPosition();
			str=dirList->GetNext(pos);	//.
			str=dirList->GetNext(pos); //..
		while(pos!=NULL)
		{
			str=dirList->GetNext(pos);
			subpath=path+str+_T("\\");
			recursiveTree(subpath, prototype);
		}
	}
	return;
}