#pragma once


// ViewFileDialog

class ViewFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(ViewFileDialog)

public:
	ViewFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	ViewFileDialog();
	virtual ~ViewFileDialog();

	virtual void OnInitDone();

	bool Show(void);
	CString getPath();
protected:
	DECLARE_MESSAGE_MAP()
};


