#include "StdAfx.h"
#include "ViewBrowseFolder.h"

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData );


ViewBrowseFolder::ViewBrowseFolder(void)
{
	

 //Info.hwndOwner = GetSafeHwnd( );  // 현재 윈도우 핸들 가져오는거, 걍 그대로 쓰세염!
 Info.hwndOwner = NULL;  // 부모 윈도우
 Info.pidlRoot = NULL; // ROOT Path 의 PID
 memset( &Info, 0, sizeof( Info ) ); // 
 Info.lpszTitle = _T("Project Root 선택");  // 
 Info.ulFlags = BIF_RETURNONLYFSDIRS; 

	Info.lpfn = BrowseCallbackProc;

	GetCurrentDirectory(MAX_PATH, path);
	Info.lParam = (LPARAM)path;	
}

ViewBrowseFolder::~ViewBrowseFolder(void)
{
}

int CALLBACK BrowseCallbackProc(HWND hWnd,	UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM) lpData);
		break;
	}
	return 0;
}


bool ViewBrowseFolder::Show(void)
{
	TCHAR TempPath[MAX_PATH];  // 임시 경로 저장
	pidlBrowse = ::SHBrowseForFolder( &Info );  // Browser 실행

	if(pidlBrowse != NULL) { 
		SHGetPathFromIDList( pidlBrowse, TempPath ); // 이렇게 하면 pszPathname에 디렉토리 위치가 저장이 됩니다.

		SetCurrentDirectory(TempPath);

		Path=CString(TempPath);
		if(Path.Right(1)!=_T("\\"))
			Path+=_T("\\");

		return true;
	}

	return false;
}

CString ViewBrowseFolder::getPath()
{
	return (CString)Path;
}