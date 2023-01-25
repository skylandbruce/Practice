#include "StdAfx.h"
#include "FindFiles.h"


FindFiles::FindFiles(void)
{
//	FileList=new CStringList();
//	DirList=new CStringList();

}


FindFiles::~FindFiles(void)
{
//	delete FileList;
//	delete DirList;
}

int FindFiles::getFileList(CString path, DWORD attribute, Entity* prototype)
{		

	CString key;
	Entity* fileInstance;
	int count=0;

	key=path;

// 시스템에서 path의 directory와 file을 읽는다
    HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	BOOL hasNext=true;

	hFind = FindFirstFile(path, &FindFileData);


	if(hFind != INVALID_HANDLE_VALUE)
	{
	   do 
	   {
		   if((FindFileData.dwFileAttributes & attribute)==0)
		   {
			   if(EntityKit::isValidFile(prototype, FindFileData.cFileName)==true)
			   {					
				   key=UtilString::reverseTrimToken(path,_T('\\'), false);
				   key+=FindFileData.cFileName;
				   fileInstance=Kit->getNewEntity(prototype, key);
				   Kit->Cache(fileInstance);
				   count++;
			   }
		   }

		   hasNext=FindNextFile(hFind, &FindFileData);

	   }while (hasNext!=0 && hasNext!=ERROR_NO_MORE_FILES);
	}
   FindClose(hFind);
   return count;
}

CStringList* FindFiles::getDirList(CString path, Entity* fileProto)
{
	Entity* Instance;

	Instance=(Entity *)Kit->getNewEntity(Kit->getPrototype(_T("DIR")), path);
	Instance->getMetaInfo()->setMetaRelativePath(RootPath);

	DirList=(CStringList*)(Instance->getValue(_T("dir")));			
	DirList->RemoveAll();
	getSelfList(path+_T("*"), DirList, fileProto);	

	Kit->Cache(Instance);
	return DirList;
}

// 확장자 filter을 설정할 수 있다
/*
// c s cpp
CStringList* FindFiles::getPathList(CString path, CString filter)
{
	DIR* dir;

	dir=(DIR *)Kit->getNewEntity(_T("DIR"), path);
	dir->setEntityPath(path);
	dir->getMetaInfo()->setMetaRelativePath(RootPath);

	getSelfList(dir, path+_T("*"), 0, filter);
//	Kit->Cache(dir);
	return DirList;
}
*/

/*
CStringList* FindFiles::getPathList(CString path, Entity* prototype)
{
	Entity* Instance;

	Instance=(Entity *)Kit->getNewEntity(prototype, path);
	Instance->setEntityPath(path);
	Instance->getMetaInfo()->setMetaRelativePath(RootPath);
	

	getSelfList(Instance, path+_T("*"), 0, prototype);
	Instance->setValue(_T("dir"), DirList);
	Instance->setValue(_T("file"), FileList);
//	Kit->Cache(Instance);
	return DirList;
}
*/


/*
void FindFiles::getSelfList(Entity* Instance, CString path, DWORD attributefilter, Entity*prototype)
{


	CString FileName;

	CString tokenFilter;
	CString tokenFileName;
	int tokenPos;
	MetaInfo meta;

	BOOL hasNext=true;
	CString FileFilter;
	CString DirFilter;

	DirList=new CStringList();
	FileList=new CStringList();

// 시스템에서 path의 directory와 file을 읽는다
    HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(path, &FindFileData);
	FileName=FindFileData.cFileName;

	if(hFind != INVALID_HANDLE_VALUE)
	{
	   do 
	   {
		   if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		   {
				DirList->AddTail(FindFileData.cFileName);

//			   DirFilter=prototype->getMetaInfo()->getMetaDirName();
//			   if(DirFilter.CompareNoCase(_T("*"))==0)
//			   {
//				DirList->AddTail(FindFileData.cFileName);
//			   }
//			   else 
//			   {
//					DirFilter.Remove(_T('*'));
//					if(FileName.Find(DirFilter)!=-1)
//						DirList->AddTail(FileName);
//			   }

		   }
		   else
		   {
			   if((FindFileData.dwFileAttributes & attributefilter)==0)
			   {
				   if(isValidFile(prototype, FileName)==true)
				   {
					FileList->AddTail(FileName);
				   }


			   }
		   }
		   hasNext=FindNextFile(hFind, &FindFileData);
		   FileName=FindFileData.cFileName;

	   }while (hasNext!=0 && hasNext!=ERROR_NO_MORE_FILES);
	}
   FindClose(hFind);
}
*/


// directory 의 리스트 채우기
void FindFiles::getSelfList(CString path, CStringList* dirList, Entity* fileProto)
{
	CString key;
	Entity* fileInstance;


   BOOL hasNext=true;

    HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(path, &FindFileData);


	if(hFind != INVALID_HANDLE_VALUE)
	{
	   do 
	   {
		   if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		   {
				dirList->AddTail(FindFileData.cFileName);
		   }
		   else
		   {
			   if(EntityKit::isValidFile(fileProto, FindFileData.cFileName)==true)
			   {
				   key=UtilString::reverseTrimToken(path,_T('\\'), false);
					key+=FindFileData.cFileName;
					
				   fileInstance=Kit->getNewEntity(fileProto, key);
					fileInstance->getMetaInfo()->setMetaRelativePath(RootPath);
				   Kit->Cache(fileInstance);
			   }
		   }
		   hasNext=FindNextFile(hFind, &FindFileData);

	   }while (hasNext!=0 && hasNext!=ERROR_NO_MORE_FILES);
	}
   FindClose(hFind);
}



/*

void FindFiles::getSelfList(CStringList* list, CString path, DWORD attributefilter, CString filter)
{
   BOOL hasNext=true;
	CString FileFilter;

    HANDLE hFind;
   WIN32_FIND_DATA FindFileData;
	
   hFind = FindFirstFile(path, &FindFileData);
    FileFilter=FindFileData.cFileName;

	if(hFind != INVALID_HANDLE_VALUE)
	{

		while (hFind != INVALID_HANDLE_VALUE) 
	   {
		   if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		   {
			   if((FindFileData.dwFileAttributes & attributefilter)==0)
			   {
				   if( filter.IsEmpty() || (FileFilter.SpanIncluding(filter)).Compare(FileFilter)==0 )
						list->AddTail(FindFileData.cFileName);		   
			   }
		   }
		   hasNext=FindNextFile(hFind, &FindFileData);
	   }
	}
   FindClose(hFind);
}
*/

// (_T("DIR"), one of _T("dir / dir_pure / file"))
/*
CStringList* FindFiles::openFiles(CString name, CString condition)
{
	CStringList* entitySet;
	entitySet=resultSet=Kit->getEntitySet(name, condition);

	return entitySet;
}
*/


/*
bool FindFiles::isValidFile(Entity* prototype, CString FileName)
{	
	CString FileFilter;

	int tokenPos;
	CString tokenFileName;
	CString tokenFilter;
	MetaInfo tokenMeta;
	MetaInfo fileMeta;

	   // prototype에 설정한 확장자 filter가 "*" 이면 무조건 Tree에 추가하고
	   // prototype에 MainFrame에서 설정했으면, filtering을 통해 추가
	   FileFilter=prototype->getMetaInfo()->getMetaFileName();
	   if(FileFilter.CompareNoCase(_T("*.*"))==0)
	   {
			return true;
	   }
	   else
	   {
	   		tokenPos=0;
			tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);
			while (tokenFileName.IsEmpty()==false)
			{
				tokenMeta.setMetaFileName(tokenFileName);
				tokenFilter=tokenMeta.getMetaFilter();
				
				fileMeta.setMetaFileName(FileName);
				if(tokenFilter.CompareNoCase(fileMeta.getMetaFilter())==0 || tokenFilter.CompareNoCase(_T("*")) == 0)
				{
					
					int index;
					
					index=tokenFileName.ReverseFind(_T('.'));
					tokenFileName=tokenFileName.Left(index);
					if(tokenFileName.Compare(_T("*"))==0)
					{
						return true;
					}

					tokenFileName.Remove(_T('*'));						
					
					index=FileName.ReverseFind(_T('.'));
					FileName=FileName.Left(index);
					
					if(FileName.Find(tokenFileName)!=-1)
					{
						return true;
					}
				}

				tokenFileName=FileFilter.Tokenize(_T(" "), tokenPos);
			}
		}
	return false;

}

*/