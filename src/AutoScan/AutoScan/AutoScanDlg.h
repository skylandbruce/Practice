// AutoScanDlg.h : 헤더 파일
//

#pragma once
#include "doAutoScan.h"
#include "afxwin.h"

// CAutoScanDlg 대화 상자
class CAutoScanDlg : public CDialog
{
protected:
	doAutoScan* pAutoScan;
// 생성입니다.
public:
	CAutoScanDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTOSCAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
	// Make File이 존재하는 드라이버 설정
	CComboBox mDriveCombo;
	// Project의 Root path를 Make File로 부터의 상대 경로로 나타냄
	CString mRootPathEdit;
	// Makefile 경로 표시
	CString mMakefileEdit;
	// // 검색 상태를 표시하는 Edit
	CString mSearchEdit;
};
