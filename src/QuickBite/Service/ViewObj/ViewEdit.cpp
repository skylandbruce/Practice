// D:\Projects\HOMEProject\FileFramework\src\QuickBite\Service\ViewObj\ViewEdit.cpp : implementation file
//

#include "stdafx.h"
#include "QuickBite.h"
#include "ViewEdit.h"


// ViewEdit

IMPLEMENT_DYNAMIC(ViewEdit, CEdit)

ViewEdit::ViewEdit()
{

}

ViewEdit::~ViewEdit()
{
}


BEGIN_MESSAGE_MAP(ViewEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// ViewEdit message handlers

afx_msg void ViewEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	switch (nChar)
	{	
		case VK_RETURN:
			UpdateData(TRUE);
//			DestroyWindow();
//			::SendMessage(this->GetParentFrame()->m_hWnd, WM_USER+1, NULL, NULL);
//			::SendMessage(this->m_hWndOwner, WM_USER+2, NULL, NULL);
			ShowWindow(SW_HIDE);
		break;
		case VK_ESCAPE:
//			DestroyWindow();
			ShowWindow(SW_HIDE);
		break;
	}

}

afx_msg void ViewEdit::OnKillFocus(CWnd* pNewWnd)
{
//	UpdateData(TRUE);
	CEdit::OnKillFocus(pNewWnd);
//	DestroyWindow();
}

