// PostItView.cpp : CPostItView 클래스의 구현
//

#include "stdafx.h"
#include "PostIt.h"

#include "PostItDoc.h"
#include "PostItView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPostItView

IMPLEMENT_DYNCREATE(CPostItView, CEditView)

BEGIN_MESSAGE_MAP(CPostItView, CEditView)
END_MESSAGE_MAP()

// CPostItView 생성/소멸

CPostItView::CPostItView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPostItView::~CPostItView()
{
}

BOOL CPostItView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
//	cs.style &= ~(ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN|WS_HSCROLL|WS_VSCROLL);	// 자동 줄바꿈을 사용합니다.
	

	return bPreCreated;
}


// CPostItView 진단

#ifdef _DEBUG
void CPostItView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPostItView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPostItDoc* CPostItView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPostItDoc)));
	return (CPostItDoc*)m_pDocument;
}
#endif //_DEBUG


// CPostItView 메시지 처리기
