// PostItView.h : CPostItView 클래스의 인터페이스
//


#pragma once


class CPostItView : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CPostItView();
	DECLARE_DYNCREATE(CPostItView)

// 특성입니다.
public:
	CPostItDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CPostItView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PostItView.cpp의 디버그 버전
inline CPostItDoc* CPostItView::GetDocument() const
   { return reinterpret_cast<CPostItDoc*>(m_pDocument); }
#endif

