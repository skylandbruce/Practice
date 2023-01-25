#pragma once

class UtilString
{
public:
	UtilString(void);
	~UtilString(void);

static	void splitFileName(CString* FileName, CString* Ext);
static	bool isSubSet(CString fullset, CString subset);
static	void replaceSet(CString withSet, CString toSet, CString* FileName);
static CString UtilString::TrimToken(CString str, CString token, bool includeToken);
static CString UtilString::reverseTrimToken(CString str, TCHAR token, bool includeToken);
};
