// PostItView.h : CPostItView Ŭ������ �������̽�
//


#pragma once


class CPostItView : public CEditView
{
protected: // serialization������ ��������ϴ�.
	CPostItView();
	DECLARE_DYNCREATE(CPostItView)

// Ư���Դϴ�.
public:
	CPostItDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CPostItView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PostItView.cpp�� ����� ����
inline CPostItDoc* CPostItView::GetDocument() const
   { return reinterpret_cast<CPostItDoc*>(m_pDocument); }
#endif

