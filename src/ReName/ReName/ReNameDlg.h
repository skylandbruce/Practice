// ReNameDlg.h : 헤더 파일
//

#pragma once
#include "doReName.h"
#include "afxwin.h"

// CReNameDlg 대화 상자
class CReNameDlg : public CDialog
{
// 생성입니다.
public:
	CReNameDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RENAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	doReName* pReName; 
	CString mFrom;
	CString mCase;
//	bool mFilterOnly;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Root Path를 표시한다
	CString mRootPath;
	// 대상 File 이나 Ext 이름 설정
	CString mWithName;
	// 새 File 이나 Ext 이름
	CString mToName;
	afx_msg void OnBnClickedRootbutton();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFromFileRadio();
	afx_msg void OnBnClickedFromDirRadio();
//	afx_msg void OnBnClickedOnlycheck();
	// File Name 선택시 Extention Only인지 체크한다
	CButton mExtOnly;
	// File Name 선택시 Extention Only가 선택되었는지 나타내는 bool 함수
	BOOL mExtOnlyChecked;
	afx_msg void OnBnClickedSearchbutton();
	// 트리검색 버튼 컨트롤
	CButton mSearchButton;
	afx_msg void OnEnChangeWithedit();
	afx_msg void OnBnClickedNocaseradio();
	afx_msg void OnBnClickedUpcaseradio();
	afx_msg void OnBnClickedLocaseradio();
};
