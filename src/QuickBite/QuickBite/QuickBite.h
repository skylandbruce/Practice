// QuickBite.h : QuickBite ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CQuickBiteApp:
// �� Ŭ������ ������ ���ؼ��� QuickBite.cpp�� �����Ͻʽÿ�.
//

class CQuickBiteApp : public CWinApp
{
public:
	CQuickBiteApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CQuickBiteApp theApp;