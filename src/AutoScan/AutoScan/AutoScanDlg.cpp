// AutoScanDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AutoScan.h"
#include "AutoScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoScanDlg 대화 상자




CAutoScanDlg::CAutoScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoScanDlg::IDD, pParent)
	, mRootPathEdit(_T(""))
	, mMakefileEdit(_T(""))
	, mSearchEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRIVERCOMBO, mDriveCombo);
	DDX_Text(pDX, IDC_ROOTEDIT, mRootPathEdit);
	DDX_Text(pDX, IDC_MAKEEDIT, mMakefileEdit);
	DDX_Text(pDX, IDC_SEARCHEDIT, mSearchEdit);
}

BEGIN_MESSAGE_MAP(CAutoScanDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ROOTBUTTON, &CAutoScanDlg::OnBnClickedRootbutton)
	ON_BN_CLICKED(IDC_LISTBUTTON, &CAutoScanDlg::OnBnClickedListbutton)
	ON_BN_CLICKED(IDC_CREATEBUTTON, &CAutoScanDlg::OnBnClickedCreatebutton)
	ON_BN_CLICKED(IDC_SEARCHBUTTON, &CAutoScanDlg::OnBnClickedSearchbutton)
	ON_BN_CLICKED(IDC_MAKEFILEBUTTON, &CAutoScanDlg::OnBnClickedMakefilebutton)
END_MESSAGE_MAP()


// CAutoScanDlg 메시지 처리기

BOOL CAutoScanDlg::OnInitDialog()
{
	CButton* pButton;
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	mMakefileEdit=_T("Make File을 선택해 주세요");
	mSearchEdit=_T("검색을 실행해 주세요");
	UpdateData(FALSE);

		pButton=(CButton*)GetDlgItem(IDC_ROOTBUTTON);
		pButton->EnableWindow(false);
		pButton=(CButton*)GetDlgItem(IDC_SEARCHBUTTON);
		pButton->EnableWindow(false);

//	mDriveCombo.AddString(_T("선택"));

	pAutoScan=new doAutoScan();    


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAutoScanDlg::OnCancel()
{
	delete pAutoScan;
	CDialog::OnCancel();
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAutoScanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAutoScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAutoScanDlg::OnBnClickedRootbutton()
{
	// TODO: Add your control notification handler code here
	CButton* pButton;

	MetaInfo* meta;

	meta=pAutoScan->getRootPath();
	if(meta != NULL)
	{	
		mRootPathEdit=meta->getMetaPath();
		UpdateData(FALSE);

		pButton=(CButton*)GetDlgItem(IDC_MAKEFILEBUTTON);
		pButton->EnableWindow(true);
		pButton=(CButton*)GetDlgItem(IDC_SEARCHBUTTON);
		pButton->EnableWindow(true);

	mSearchEdit=_T("검색을 실행해 주세요");
	UpdateData(FALSE);
	}
}

void CAutoScanDlg::OnBnClickedListbutton()
{
	// TODO: Add your control notification handler code here

}

void CAutoScanDlg::OnBnClickedCreatebutton()
{
	// TODO: Add your control notification handler code here
	pAutoScan->createConfigure();
}

void CAutoScanDlg::OnBnClickedSearchbutton()
{
	// TODO: Add your control notification handler code here
	CButton* pButton;

	pAutoScan->getTreeList();

	pButton=(CButton*)GetDlgItem(IDC_LISTBUTTON);
	pButton->EnableWindow(true);

	pButton=(CButton*)GetDlgItem(IDC_CREATEBUTTON);
	pButton->EnableWindow(true);

	mSearchEdit=_T("검색완료!!!");
	UpdateData(FALSE);
//	pcommentStatic->SetWindowTextA(_T("소스 리스트를 수정할 수 있습니다"));
}

void CAutoScanDlg::OnBnClickedMakefilebutton()
{
	// TODO: Add your control notification handler code here
	CButton* pButton;

	MetaInfo* meta;
	meta=pAutoScan->getMakeFile();
	if(meta != NULL)
	{	
		mDriveCombo.AddString(meta->getMetaDrive());
		mDriveCombo.SetCurSel(0);

		mMakefileEdit=meta->getMetaFullPathName();
		UpdateData(FALSE);

		pButton=(CButton*)GetDlgItem(IDC_ROOTBUTTON);
		pButton->EnableWindow(true);
		pButton=(CButton*)GetDlgItem(IDC_MAKEFILEBUTTON);
		pButton->EnableWindow(false);
		pButton=(CButton*)GetDlgItem(IDC_SEARCHBUTTON);
		pButton->EnableWindow(false);

	mSearchEdit=_T("검색을 실행해 주세요");
	UpdateData(FALSE);
	}
}
