// PostItDoc.cpp : CPostItDoc Ŭ������ ����
//

#include "stdafx.h"
#include "PostIt.h"

#include "PostItDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPostItDoc

IMPLEMENT_DYNCREATE(CPostItDoc, CDocument)

BEGIN_MESSAGE_MAP(CPostItDoc, CDocument)
END_MESSAGE_MAP()


// CPostItDoc ����/�Ҹ�

CPostItDoc::CPostItDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CPostItDoc::~CPostItDoc()
{
}

BOOL CPostItDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CPostItDoc serialization

void CPostItDoc::Serialize(CArchive& ar)
{
	// CEditView���� ��� serialization�� ó���ϴ� edit ��Ʈ���� ��� �ֽ��ϴ�.
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CPostItDoc ����

#ifdef _DEBUG
void CPostItDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPostItDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPostItDoc ���
