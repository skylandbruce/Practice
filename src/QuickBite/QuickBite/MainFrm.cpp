// MainFrm.cpp : CMainFrame Ŭ������ ����
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
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	QuickBite.getRootPath();

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// �������� Ŭ���̾�Ʈ ������ �����ϴ� �並 ����ϴ�.
// View�� ������� �ʴ´�
/*
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("�� â�� ������ ���߽��ϴ�.\n");
		return -1;
	}
*/

// �ڵ� �߰�
	QuickBite.doConfigure(this);

// Status Bar ������� �ʴ´�
/*
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	RECT Rect;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		|WS_MINIMIZEBOX | WS_SYSMENU;

// �Ӽ�����
	// ũ������ ���ϵ��� ����
//	| WS_THICKFRAME 

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

// ������ ũ�� ���� �߰�
	cs.cx=FRAME_WIDTH;
	cs.cy=FRAME_HEIGHT;

	this->GetDesktopWindow()->GetWindowRect(&Rect);
	cs.x=Rect.right-FRAME_WIDTH;
	cs.y=Rect.top+50;
	return TRUE;
}


// CMainFrame ����

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


// CMainFrame �޽��� ó����

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// �� â���� ��Ŀ���� �̵��մϴ�.
// View�� ������� �ʴ´�
//	m_wndView.SetFocus();

// �׻� �ֻ��� ������� ����
//	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
	
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// �信�� ù° ũ���� �ش� ��ɿ� ��Ÿ������ �մϴ�.
// View�� ������� �ʴ´�
//	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//		return TRUE;

	// �׷��� ������ �⺻ ó���մϴ�.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// ViewBitmapButton ���� ���� ����� �޽��� ó��
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
