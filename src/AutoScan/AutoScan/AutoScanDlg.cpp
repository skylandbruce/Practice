// AutoScanDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AutoScan.h"
#include "AutoScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoScanDlg ��ȭ ����




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


// CAutoScanDlg �޽��� ó����

BOOL CAutoScanDlg::OnInitDialog()
{
	CButton* pButton;
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	mMakefileEdit=_T("Make File�� ������ �ּ���");
	mSearchEdit=_T("�˻��� ������ �ּ���");
	UpdateData(FALSE);

		pButton=(CButton*)GetDlgItem(IDC_ROOTBUTTON);
		pButton->EnableWindow(false);
		pButton=(CButton*)GetDlgItem(IDC_SEARCHBUTTON);
		pButton->EnableWindow(false);

//	mDriveCombo.AddString(_T("����"));

	pAutoScan=new doAutoScan();    


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAutoScanDlg::OnCancel()
{
	delete pAutoScan;
	CDialog::OnCancel();
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAutoScanDlg::OnPaint()
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

	mSearchEdit=_T("�˻��� ������ �ּ���");
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

	mSearchEdit=_T("�˻��Ϸ�!!!");
	UpdateData(FALSE);
//	pcommentStatic->SetWindowTextA(_T("�ҽ� ����Ʈ�� ������ �� �ֽ��ϴ�"));
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

	mSearchEdit=_T("�˻��� ������ �ּ���");
	UpdateData(FALSE);
	}
}
