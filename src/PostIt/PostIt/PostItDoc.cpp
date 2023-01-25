// PostItDoc.cpp : CPostItDoc 클래스의 구현
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


// CPostItDoc 생성/소멸

CPostItDoc::CPostItDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CPostItDoc::~CPostItDoc()
{
}

BOOL CPostItDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CPostItDoc serialization

void CPostItDoc::Serialize(CArchive& ar)
{
	// CEditView에는 모든 serialization을 처리하는 edit 컨트롤이 들어 있습니다.
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CPostItDoc 진단

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


// CPostItDoc 명령
