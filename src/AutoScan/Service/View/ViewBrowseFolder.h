#pragma once


class ViewBrowseFolder
{
protected:
	// Browser 의 환경설정 구조체
	BROWSEINFO Info;
	// 경로 저장을 위한 변수
	CString RelativePath;
	CString Path;
	ITEMIDLIST *pidlBrowse; // 구조체 초기화

	TCHAR path[MAX_PATH];

public:
	ViewBrowseFolder(void);
	~ViewBrowseFolder(void);

	bool Show(void);
	CString getPath();
};
