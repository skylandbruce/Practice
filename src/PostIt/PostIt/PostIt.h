// PostIt.h : PostIt ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPostItApp:
// �� Ŭ������ ������ ���ؼ��� PostIt.cpp�� �����Ͻʽÿ�.
//

class CPostItApp : public CWinApp
{
public:
	CPostItApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPostItApp theApp;