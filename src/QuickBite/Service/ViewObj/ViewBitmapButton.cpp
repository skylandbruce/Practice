// D:\Projects\HOMEProject\FileFramework\src\QuickBite\Service\BizObj\ViewBitmapButton.cpp : implementation file
//

#include "stdafx.h"

#include "ViewBitmapButton.h"
#include "ViewFileDialog.h"


// ViewBitmapButton


IMPLEMENT_DYNAMIC(ViewBitmapButton, CBitmapButton)

ViewBitmapButton::ViewBitmapButton()
{
	rect=CRect(0,0,BUTTON_WIDTH,BUTTON_HEIGHT);
}

ViewBitmapButton::~ViewBitmapButton()
{
}

// 구현 함수
void ViewBitmapButton::Create(CWnd* pParentWnd, int index)
{
	CString* strTitle;
//	LPCTSTR title;
//	title=(LPCTSTR)exeFile->getValue(_T("title"));
//	title=_T("실행버튼");
	strTitle= (CString*)(exeFile->getValue(_T("title")))  ;

	rect.top=BUTTON_HEIGHT*index;
	rect.bottom=rect.top+BUTTON_HEIGHT;

	CBitmapButton::Create( *strTitle, WS_CHILD|WS_VISIBLE|/*BS_OWNERDRAW*//*BS_BITMAP*/BS_PUSHBUTTON, rect, pParentWnd, index+1 ); // ID는 1부터시작
//	CBitmapButton::LoadBitmaps("IDB_UP","IDB_DOWN", "IDB_FOCUS", "IDB_DISABLE");
	//	CBitmapButton::AutoLoad(index+1, pParentWnd);;


}




void ViewBitmapButton::setExeFile(Entity* file)
{
	exeFile=file;
}

bool ViewBitmapButton::setExeFile(void)
{	
	CString ExeFilePath;
	CString* strTitle=new CString(_T("QuickBite"));
	bool ret=false;
	ViewFileDialog* BrowseFile = new ViewFileDialog();

	if(BrowseFile->Show() == true)
	{
		ExeFilePath=BrowseFile->getPath();
		exeFile->getMetaInfo()->setMetaFullPathName(ExeFilePath);
		exeFile->setValue(_T("title"), (CObject*)strTitle); 
		SetWindowTextA(*strTitle);
		ret=true;
	}

	delete BrowseFile;

	return ret;
}


BEGIN_MESSAGE_MAP(ViewBitmapButton, CBitmapButton)
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()

	ON_WM_TIMER()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()




// ViewBitmapButton message handlers

/*
TCHAR szSel[]=TEXT("calc.exe");

LRESULT ViewBitmapButton::WindowProc(
   UINT message,
   WPARAM wParam,
   LPARAM lParam 
   )
{
	CString pathfile;
	
    switch(message)
    {
		case WM_LBUTTONDOWN:

			break;
		case WM_LBUTTONUP:
			pathfile=exeFile->getMetaInfo()->getMetaFullPathName();
			if(pathfile.IsEmpty()==true);
//				CreateProcessW(pathfile,_T(""),NULL,NULL,FALSE,NULL,NULL,NULL,NULL,lpProcessInfo);
			break;
		default:

			break;

	}
	CWnd::WindowProc(message, wParam, lParam);
	return TRUE;
}
*/

enum TIMER_MSG
{
	IDT_LBUTTONDOWN=1, // non zero
	IDT_RBUTTONDOWN
};

#define SATTLE_TIME 500

afx_msg void ViewBitmapButton::OnLButtonDown(
   UINT nFlags,
   CPoint point 
)
{
	UINT  uResult;
	uResult = SetTimer(//this,             // handle to main window 
		IDT_LBUTTONDOWN,                   // timer identifier 
		SATTLE_TIME,                           // 0.5-second interval 
		(TIMERPROC) NULL);               // no timer callback 
}

/*
afx_msg void ViewBitmapButton::OnLButtonUp(
   UINT nFlags,
   CPoint point 
)
{
	CString key;
	CString pathfile;


		pathfile=exeFile->getMetaInfo()->getMetaFullPathName();
		if(pathfile.IsEmpty()==true)
		{
			setExeFile();
		}
		else
		{
			key=exeFile->getKey();
			AfxMessageBox(pathfile+_T("프로그램 실행!")+key);	
		}

}
*/
void ViewBitmapButton::OnLButtonUp()
{
	CString pathfile;

		pathfile=exeFile->getMetaInfo()->getMetaFullPathName();
		if(pathfile.IsEmpty()==true)
		{
			setExeFile();
		}
		else
		{
			WinExec(pathfile,SW_SHOW);
//			pathfile.GetString();
//			CreateProcessW(pathfile,_T(""),NULL,NULL,FALSE,NULL,NULL,NULL,NULL,lpProcessInfo);
//			str.ReleaseBuffer(); 
//			CorLaunchApplication
			
//			AfxMessageBox(pathfile+_T("프로그램 실행!"));	
		}

}

afx_msg void ViewBitmapButton::OnLButtonDblClk(
   UINT nFlags,
   CPoint point 
)
{
	doubleClick=true;
	::SendMessage(this->GetParentFrame()->m_hWnd, WM_LBUTTONDBLCLK, NULL, NULL);

}

afx_msg void ViewBitmapButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	UINT  uResult;
	uResult = SetTimer(//this,             // handle to main window 
		IDT_RBUTTONDOWN,                   // timer identifier 
		SATTLE_TIME,                           // 0.5-second interval 
		(TIMERPROC) NULL);               // no timer callback 
}

/*
afx_msg void ViewBitmapButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	CString ExeFilePath;
	if(isBasic==true)
	{
		ViewFileDialog* BrowseFile = new ViewFileDialog();

		setExeFile();

		delete BrowseFile;
	}
}
*/

void ViewBitmapButton::OnRButtonUp()
{
//	CString ExeFilePath;

//		ViewFileDialog* BrowseFile = new ViewFileDialog();

		setExeFile();

//		delete BrowseFile;
	
}

afx_msg void ViewBitmapButton::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	CString *strTitle;
	doubleClick=true;

	viewEdit=new ViewEdit();
	viewEdit->Create(WS_CHILD|WS_VISIBLE|ES_CENTER, CRect(EDIT_WMARGIN,EDIT_HMARGIN,BUTTON_WIDTH-EDIT_WMARGIN,BUTTON_HEIGHT-EDIT_HMARGIN), this, 100);
	strTitle= (CString*)(exeFile->getValue(_T("title")));
	viewEdit->SetWindowTextA(*strTitle);

	

/*
	CString* Title = new CString(_T("실행변경"));
	exeFile->setValue(_T("title"), (CObject*)Title);
*/
//	CButton::SetWindowTextA(*Title);
}


afx_msg void ViewBitmapButton::OnTimer( UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDT_LBUTTONDOWN:

		KillTimer(nIDEvent);
		if(doubleClick==true)
			doubleClick=false;
		else
			OnLButtonUp();


		break;	
	case IDT_RBUTTONDOWN:
		KillTimer(nIDEvent);
		if(doubleClick==true)
			doubleClick=false;
		else
			OnRButtonUp();


		break;	
	}
	CBitmapButton::OnTimer(nIDEvent);
}

afx_msg void ViewBitmapButton::OnSetFocus(CWnd* pOldWnd)
{
	if(IsChild(pOldWnd) == TRUE)
	{
		CString* strTitle=new CString();
		viewEdit->GetWindowTextA(*strTitle);
		viewEdit->DestroyWindow();
		delete viewEdit;

		exeFile->setValue(_T("title"), (CObject*)strTitle);
		SetWindowTextA(*strTitle);
	}
	CBitmapButton::OnSetFocus(pOldWnd);
}