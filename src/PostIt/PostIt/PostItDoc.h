// PostItDoc.h : CPostItDoc Ŭ������ �������̽�
//


#pragma once


class CPostItDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CPostItDoc();
	DECLARE_DYNCREATE(CPostItDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CPostItDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


