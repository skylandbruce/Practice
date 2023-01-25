// D:\Projects\HOMEProject\AutoScan\src\AutoScan\Service\AutoScan\View\ViewFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ViewFileDialog.h"


// ViewFileDialog

IMPLEMENT_DYNAMIC(ViewFileDialog, CFileDialog)

ViewFileDialog::ViewFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

}

ViewFileDialog::ViewFileDialog(): CFileDialog(TRUE, // Open
											_T("EXE"), // default extension
											_T("*.EXE"), // initial file name
											OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
											CString("Make file (*.EXE)|*.EXE|*.*|*.*|")
										)
{
}

ViewFileDialog::~ViewFileDialog()
{
}


void ViewFileDialog::OnInitDone()
{
	CWnd* pFD = GetParent();
//파일이름	00000442
//combo2	0000047c
//	HideControl(0x00000441); // 파일형식
//	HideControl(0x00000470); // CCombo

//	SetControlText(0x00000442, _T("폴더 선택"));	
	SetControlText(IDOK, _T("선택"));
	pFD->SetWindowText(_T("실행가능한 FILE을 선택해 주세요"));
}

bool ViewFileDialog::Show()
{
	bool ret=false;
	if(this->DoModal()== IDOK)
	{
		ret= true;
	}
	return ret;

}

CString ViewFileDialog::getPath()
{	
	return GetPathName();
}

BEGIN_MESSAGE_MAP(ViewFileDialog, CFileDialog)
END_MESSAGE_MAP()



// ViewFileDialog message handlers


