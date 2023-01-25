// D:\Projects\HOMEProject\AutoScan\src\AutoScan\Service\AutoScan\View\ViewFolderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "AutoScan.h"
#include "ViewFolderDialog.h"





// ViewFolderDialog

IMPLEMENT_DYNAMIC(ViewFolderDialog, CFileDialog)

ViewFolderDialog::ViewFolderDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

ViewFolderDialog::ViewFolderDialog() : CFileDialog(TRUE, NULL, _T("*..*"))
{
}

ViewFolderDialog::~ViewFolderDialog()
{
}

WNDPROC m_wndProc;

LRESULT CALLBACK WindowProcNew(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	
	if (message ==  WM_COMMAND)
		if (HIWORD(wParam) == BN_CLICKED)
			if (LOWORD(wParam) == IDOK)
			{
				if (CFileDialog* pDlg = (CFileDialog*)CWnd::FromHandle(hwnd))
				{
					pDlg->EndDialog(IDOK);
					return NULL;
				}
			}
	return CallWindowProc(m_wndProc, hwnd, message, wParam, lParam);
}

void ViewFolderDialog::OnInitDone()
{
	CWnd* pFD = GetParent();
	
//	HideControl(IDCANCEL);
//	HideControl(IDOK);
//	HideControl(0x00000442); // 파일이름
//	HideControl(0x0000047c); // CCombo

	HideControl(0x00000441); // 파일형식
	HideControl(0x00000470); // CCombo
/*
	CRect rectCancel; pFD->GetDlgItem(IDCANCEL)->GetWindowRect(rectCancel);
	pFD->ScreenToClient(rectCancel);
	CRect rectOK; pFD->GetDlgItem(IDOK)->GetWindowRect(rectOK);
	pFD->ScreenToClient(rectOK);
	pFD->GetDlgItem(IDOK)->SetWindowPos(0,rectCancel.left - rectOK.Width() - 4, rectCancel.top, 0,0, SWP_NOZORDER | SWP_NOSIZE);

	CRect rectList2; 
	pFD->GetDlgItem(lst1)->GetWindowRect(rectList2);
	pFD->ScreenToClient(rectList2);
	pFD->GetDlgItem(lst1)->SetWindowPos(0,0,0,rectList2.Width(), abs(rectList2.top - (rectCancel.top - 4)), SWP_NOMOVE | SWP_NOZORDER);
*/
	SetControlText(0x00000442, _T("폴더 선택"));	
	SetControlText(IDOK, _T("선택"));
	pFD->SetWindowText(_T("Project Root 경로를 선택해 주세요"));
	m_wndProc = (WNDPROC)SetWindowLong(pFD->m_hWnd, GWL_WNDPROC, (LONG)WindowProcNew);
}


BEGIN_MESSAGE_MAP(ViewFolderDialog, CFileDialog)
//	ON_BN_CLICKED(IDCANCEL, &ViewFolderDialog::OnBnClickedSelect)

END_MESSAGE_MAP()



// ViewFolderDialog message handlers
/*
void ViewFolderDialog::OnBnClickedSelect()
{

}
*/

void ViewFolderDialog::OnFileNameChange()
{

}

void ViewFolderDialog::OnFolderChange( )
{
//	OPENFILENAME lpofn;
	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);
	Path=CString(path);

//	m_ofn.lpstrFile=path;
//	ofn->lpstrFile=Path;
}


bool ViewFolderDialog::Show()
{
	bool ret=false;
	if(this->DoModal()== IDOK)
	{
		ret= true;
	}
	return ret;

}

CString ViewFolderDialog::getPath()
{
//	Path=GetPathName();
	return Path;
}