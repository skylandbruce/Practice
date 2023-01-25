#pragma once


// ViewEdit

class ViewEdit : public CEdit
{
	DECLARE_DYNAMIC(ViewEdit)

public:
	ViewEdit();
	virtual ~ViewEdit();

protected:
afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
afx_msg void OnKillFocus(CWnd* pNewWnd);
	DECLARE_MESSAGE_MAP()
};


