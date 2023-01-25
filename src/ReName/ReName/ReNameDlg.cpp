// ReNameDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ReName.h"
#include "ReNameDlg.h"

#include "MetaInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReNameDlg ��ȭ ����




CReNameDlg::CReNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReNameDlg::IDD, pParent)
	, mRootPath(_T(""))
	, mWithName(_T(""))
	, mToName(_T(""))
	, mExtOnlyChecked(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROOTEDIT, mRootPath);
	DDX_Text(pDX, IDC_WITHEDIT, mWithName);
	DDX_Text(pDX, IDC_TOEDIT, mToName);
	DDX_Control(pDX, IDC_ONLYCHECK, mExtOnly);
	DDX_Check(pDX, IDC_ONLYCHECK, mExtOnlyChecked);
	DDX_Control(pDX, IDC_SEARCHBUTTON, mSearchButton);
}

BEGIN_MESSAGE_MAP(CReNameDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ROOTBUTTON, &CReNameDlg::OnBnClickedRootbutton)
	ON_BN_CLICKED(IDOK, &CReNameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_FILERADIO, &CReNameDlg::OnBnClickedFromFileRadio)
	ON_BN_CLICKED(IDC_DIRRADIO, &CReNameDlg::OnBnClickedFromDirRadio)
//	ON_BN_CLICKED(IDC_ONLYCHECK, &CReNameDlg::OnBnClickedOnlycheck)
ON_BN_CLICKED(IDC_SEARCHBUTTON, &CReNameDlg::OnBnClickedSearchbutton)
ON_EN_CHANGE(IDC_WITHEDIT, &CReNameDlg::OnEnChangeWithedit)
ON_BN_CLICKED(IDC_NOCASERADIO, &CReNameDlg::OnBnClickedNocaseradio)
ON_BN_CLICKED(IDC_UPCASERADIO, &CReNameDlg::OnBnClickedUpcaseradio)
ON_BN_CLICKED(IDC_LOCASERADIO, &CReNameDlg::OnBnClickedLocaseradio)
END_MESSAGE_MAP()


// CReNameDlg �޽��� ó����

BOOL CReNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	pReName=new doReName();

	CheckRadioButton(IDC_FILERADIO, IDC_DIRRADIO, IDC_FILERADIO);
	mFrom=_T("file");
	CheckRadioButton(IDC_NOCASERADIO, IDC_LOCASERADIO, IDC_NOCASERADIO);
	mCase=_T("nocase");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReNameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReNameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReNameDlg::OnBnClickedRootbutton()
{
	// TODO: Add your control notification handler code here
	MetaInfo* meta;
	meta=pReName->getRootPath();

	if(meta==NULL) return;
	mRootPath=meta->getMetaPath();
	UpdateData(FALSE);
	mSearchButton.EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(false);	
}

void CReNameDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	BOOL checked;
	CString token(_T(" "));

	if( mFrom.Compare(_T("dir"))==0 )
	{
		checked=false;
	}
	else
	{
		checked=mExtOnlyChecked;
	}
	pReName->doConfigure(mFrom, mWithName, mToName, mCase, checked);


	pReName->doAction(mFrom);
//	OnOK();
}

void CReNameDlg::OnBnClickedFromFileRadio()
{
	// TODO: Add your control notification handler code here
	mFrom=_T("file");
	mExtOnly.EnableWindow(1);
	GetDlgItem(IDOK)->EnableWindow(false);	
}

void CReNameDlg::OnBnClickedFromDirRadio()
{
	// TODO: Add your control notification handler code here
	mFrom=_T("dir");
	mExtOnlyChecked=false;
	mExtOnly.EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(false);	
}

/*
void CReNameDlg::OnBnClickedOnlycheck()
{
	// TODO: Add your control notification handler code here
}
*/

void CReNameDlg::OnBnClickedSearchbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(mFrom.Compare(_T("file"))==0)
		pReName->setFileName(mWithName);
	else
		pReName->setDirName(mWithName);

	pReName->getTreeList();
	GetDlgItem(IDOK)->EnableWindow(true);

}

void CReNameDlg::OnEnChangeWithedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	GetDlgItem(IDOK)->EnableWindow(false);	
}

void CReNameDlg::OnBnClickedNocaseradio()
{
	// TODO: Add your control notification handler code here
	mCase=_T("nocase");
}

void CReNameDlg::OnBnClickedUpcaseradio()
{
	// TODO: Add your control notification handler code here
	mCase=_T("upcase");
}

void CReNameDlg::OnBnClickedLocaseradio()
{
	// TODO: Add your control notification handler code here
	mCase=_T("locase");
}
