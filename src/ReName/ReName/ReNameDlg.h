// ReNameDlg.h : ��� ����
//

#pragma once
#include "doReName.h"
#include "afxwin.h"

// CReNameDlg ��ȭ ����
class CReNameDlg : public CDialog
{
// �����Դϴ�.
public:
	CReNameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RENAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	doReName* pReName; 
	CString mFrom;
	CString mCase;
//	bool mFilterOnly;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Root Path�� ǥ���Ѵ�
	CString mRootPath;
	// ��� File �̳� Ext �̸� ����
	CString mWithName;
	// �� File �̳� Ext �̸�
	CString mToName;
	afx_msg void OnBnClickedRootbutton();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFromFileRadio();
	afx_msg void OnBnClickedFromDirRadio();
//	afx_msg void OnBnClickedOnlycheck();
	// File Name ���ý� Extention Only���� üũ�Ѵ�
	CButton mExtOnly;
	// File Name ���ý� Extention Only�� ���õǾ����� ��Ÿ���� bool �Լ�
	BOOL mExtOnlyChecked;
	afx_msg void OnBnClickedSearchbutton();
	// Ʈ���˻� ��ư ��Ʈ��
	CButton mSearchButton;
	afx_msg void OnEnChangeWithedit();
	afx_msg void OnBnClickedNocaseradio();
	afx_msg void OnBnClickedUpcaseradio();
	afx_msg void OnBnClickedLocaseradio();
};
