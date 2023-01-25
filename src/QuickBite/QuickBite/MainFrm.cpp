// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "QuickBite.h"

#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_ADDBUTTON, &CMainFrame::OnAddbutton)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	QuickBite.getRootPath();

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
// View는 사용하지 않는다
/*
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}
*/

// 코드 추가
	QuickBite.doConfigure(this);

// Status Bar 사용하지 않는다
/*
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	RECT Rect;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		|WS_MINIMIZEBOX | WS_SYSMENU;

// 속성제거
	// 크기조절 못하도록 제거
//	| WS_THICKFRAME 

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

// 윈도우 크기 변경 추가
	cs.cx=FRAME_WIDTH;
	cs.cy=FRAME_HEIGHT;

	this->GetDesktopWindow()->GetWindowRect(&Rect);
	cs.x=Rect.right-FRAME_WIDTH;
	cs.y=Rect.top+50;
	return TRUE;
}


// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
// View는 사용하지 않는다
//	m_wndView.SetFocus();

// 항상 최상위 윈도우로 지정
//	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
	
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
// View는 사용하지 않는다
//	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// ViewBitmapButton 에서 부터 날라온 메시지 처리
afx_msg void CMainFrame::OnLButtonDblClk(
   UINT nFlags,
   CPoint point 
)
{
	QuickBite.doExtend(this);	
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void CMainFrame::OnAddbutton()
{
	// TODO: Add your command handler code here
	QuickBite.addNewButton(this);
}
