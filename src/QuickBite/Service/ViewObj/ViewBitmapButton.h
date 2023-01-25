#pragma once

// ViewBitmapButton
#include "Entity.h"
#include "ViewEdit.h"

#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 40//60
#define EDIT_HMARGIN 10//20
#define EDIT_WMARGIN 5

#define FRAME_WIDTH 126
#define FRAME_HEIGHT 84//103       //104//123

class ViewBitmapButton : public CBitmapButton
{
	DECLARE_DYNAMIC(ViewBitmapButton)

// ±¸Çö
protected:
	Entity* exeFile;
	CRect rect;

	LPPROCESS_INFORMATION lpProcessInfo;

	bool doubleClick;

	ViewEdit* viewEdit;

public:
	void Create(CWnd* pParentWnd, int index);
	Entity* getExeFile(void);
	void setExeFile(Entity* file);
	bool setExeFile(void);

public:
	ViewBitmapButton();
	virtual ~ViewBitmapButton();

protected:
//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
/*
afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
*/
	void OnLButtonUp();

afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);


afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
/*
afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
*/
	void OnRButtonUp();
afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);


afx_msg void OnTimer(UINT_PTR nIDEvent);

afx_msg void OnSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()
};


