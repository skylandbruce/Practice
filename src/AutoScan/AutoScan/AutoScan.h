// AutoScan.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAutoScanApp:
// �� Ŭ������ ������ ���ؼ��� AutoScan.cpp�� �����Ͻʽÿ�.
//

class CAutoScanApp : public CWinApp
{
public:
	CAutoScanApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAutoScanApp theApp;