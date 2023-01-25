#pragma once


// ViewFolderDialog


class ViewFolderDialog : public CFileDialog
{
	DECLARE_DYNAMIC(ViewFolderDialog)
protected:
		CString Path;

public:
	ViewFolderDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	ViewFolderDialog();
	virtual ~ViewFolderDialog();

	virtual void OnInitDone();
//	afx_msg void OnBnClickedSelect();
	virtual void OnFileNameChange();
	virtual void OnFolderChange();

	bool Show(void);
	CString getPath();
protected:
	DECLARE_MESSAGE_MAP()
};


