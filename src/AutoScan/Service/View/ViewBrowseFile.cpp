#include "StdAfx.h"
#include "ViewBrowseFile.h"

ViewBrowseFile::ViewBrowseFile(void)
{

	FileName=_T("");
	Filter=_T("");
	FullPath=_T("");	
	Drive=_T("");
	FullPathName=_T("");

	Init();
	/*
	ViewFindFiles *FindFile = new ViewFindFiles(
		TRUE, // Open
		NULL, // No default extensio
		_T("Make file (*.MAK)|*.MAK|*.*|*.*"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY		
		);
	FindFile.DoModal();



	ViewFindFiles FindFiles(TRUE, // Open
		NULL, // No default extension
		NULL, // No initial file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		CString("Make file (*.MAK)|*.MAK|*.*|*.*|")
	);
	FindFiles.DoModal();
*/
}

ViewBrowseFile::~ViewBrowseFile(void)
{
}

void ViewBrowseFile::Init(void)
{
	FileDialog = new CFileDialog(TRUE, // Open
		_T("MAK"), // No default extension
		_T("*.MAK"), // No initial file name
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		CString("Make file (*.MAK)|*.MAK|*.*|*.*|")
	);
}


bool ViewBrowseFile::Show(void)
{
	bool ret=false;
	if(FileDialog->DoModal()== IDOK)
	{
		FileName=	FileDialog->GetFileName();
		Filter=		FileDialog->GetFileExt();
		FullPathName=	FileDialog->GetPathName();
		FullPath=	FileDialog->GetPathName();
		FullPath=	FullPath.TrimRight(FileName); // GetPathName 결과에서 FileName 제거
		Drive=		FullPath.Left(3);
	ret= true;
	}
	delete FileDialog;
	return ret;

}

/*
void fillMetaInfo(MetaInfo* Info)
{
	Info->setMetaFullPathName(FullPathName);
	Info->setMetaPath(FullPath);
	Info->setMetaFileName(FileName);
	Info->setMetaFilter(Filter);
	Info->setMetaDrive(Drive);
}
*/

CString ViewBrowseFile::getPath()
{
	return FullPathName;
}

CString ViewBrowseFile::getFullPathName()
{
	return FullPathName;
}

CString ViewBrowseFile::getFullPath()
{
	return FullPath;
}

CString ViewBrowseFile::getFileName()
{
	return FileName;
}

CString ViewBrowseFile::getFilter()
{
	return Filter;
}

CString ViewBrowseFile::getDrive()
{
	return Drive;
}