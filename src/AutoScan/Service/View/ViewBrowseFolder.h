#pragma once


class ViewBrowseFolder
{
protected:
	// Browser �� ȯ�漳�� ����ü
	BROWSEINFO Info;
	// ��� ������ ���� ����
	CString RelativePath;
	CString Path;
	ITEMIDLIST *pidlBrowse; // ����ü �ʱ�ȭ

	TCHAR path[MAX_PATH];

public:
	ViewBrowseFolder(void);
	~ViewBrowseFolder(void);

	bool Show(void);
	CString getPath();
};
