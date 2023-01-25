#pragma once
//#include "MetaInfo.h"

class ViewBrowseFile
{
protected:
	CFileDialog *FileDialog;

	CString FullPathName;	
	CString FullPath;	// DRIVE:/PATH/
	CString FileName;	// Name.EXT
	CString Filter;		// EXT
	CString Drive;		// DRIVE/
	
protected:
	void Init(void);

public:
	ViewBrowseFile(void);
	~ViewBrowseFile(void);

	bool Show(void);
//	void fillMetaInfo(MetaInfo* Info);
	CString getPath();
	CString getFullPathName();	
	CString getFullPath();
	CString getFileName();
	CString getFilter();
	CString getDrive();
};
