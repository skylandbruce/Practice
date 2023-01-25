// AutoScanDlg.h : ��� ����
//

#pragma once
#include "doAutoScan.h"
#include "afxwin.h"

// CAutoScanDlg ��ȭ ����
class CAutoScanDlg : public CDialog
{
protected:
	doAutoScan* pAutoScan;
// �����Դϴ�.
public:
	CAutoScanDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTOSCAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRootbutton();
	afx_msg void OnBnClickedListbutton();
	afx_msg void OnBnClickedCreatebutton();
	afx_msg void OnBnClickedSearchbutton();
	afx_msg void OnBnClickedMakefilebutton();
	// Make File�� �����ϴ� ����̹� ����
	CComboBox mDriveCombo;
	// Project�� Root path�� Make File�� ������ ��� ��η� ��Ÿ��
	CString mRootPathEdit;
	// Makefile ��� ǥ��
	CString mMakefileEdit;
	// // �˻� ���¸� ǥ���ϴ� Edit
	CString mSearchEdit;
};
