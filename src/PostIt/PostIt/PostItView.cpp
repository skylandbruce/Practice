// PostItView.cpp : CPostItView Ŭ������ ����
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

// CPostItView ����/�Ҹ�

CPostItView::CPostItView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CPostItView::~CPostItView()
{
}

BOOL CPostItView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
//	cs.style &= ~(ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN|WS_HSCROLL|WS_VSCROLL);	// �ڵ� �ٹٲ��� ����մϴ�.
	

	return bPreCreated;
}


// CPostItView ����

#ifdef _DEBUG
void CPostItView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPostItView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPostItDoc* CPostItView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPostItDoc)));
	return (CPostItDoc*)m_pDocument;
}
#endif //_DEBUG


// CPostItView �޽��� ó����
