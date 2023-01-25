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
//�����̸�	00000442
//combo2	0000047c
//	HideControl(0x00000441); // ��������
//	HideControl(0x00000470); // CCombo

//	SetControlText(0x00000442, _T("���� ����"));	
	SetControlText(IDOK, _T("����"));
	pFD->SetWindowText(_T("���డ���� FILE�� ������ �ּ���"));
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


