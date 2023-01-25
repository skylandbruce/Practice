#include "StdAfx.h"
#include "ViewBrowseFolder.h"

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData );


ViewBrowseFolder::ViewBrowseFolder(void)
{
	

 //Info.hwndOwner = GetSafeHwnd( );  // ���� ������ �ڵ� �������°�, �� �״�� ������!
 Info.hwndOwner = NULL;  // �θ� ������
 Info.pidlRoot = NULL; // ROOT Path �� PID
 memset( &Info, 0, sizeof( Info ) ); // 
 Info.lpszTitle = _T("Project Root ����");  // 
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
	TCHAR TempPath[MAX_PATH];  // �ӽ� ��� ����
	pidlBrowse = ::SHBrowseForFolder( &Info );  // Browser ����

	if(pidlBrowse != NULL) { 
		SHGetPathFromIDList( pidlBrowse, TempPath ); // �̷��� �ϸ� pszPathname�� ���丮 ��ġ�� ������ �˴ϴ�.

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