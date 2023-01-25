#pragma once
#include "Framework.h"
#include "ViewBrowseFolder.h"
#include "UtilString.h"

class doReName : public Framework
{
protected:
	CString RootPath;
public:
	doReName(void);
	~doReName(void);

    // 오버라이딩 함수
//////////////////////////////////////////////
protected:
virtual	void init();
virtual	void initService();

protected:
	// Root 의 경로 지정
	ViewBrowseFolder* BrowseFolder;
	bool setRoot(void);
virtual	void updateRoot(void);
public:
	MetaInfo* getRootPath(void);


	// TreeList 생성
	void setFileName(CString fileName);
	void setDirName(CString dirName);
	void getTreeList(void);
//	void getTreeList(CString filter);

protected:
	void openReName(void);
	void saveReName(CString objName);
public:
	void doConfigure(CString from, CString withFileName, CString toFileName, CString Case, BOOL extOnly);
	void doAction(CString from);

friend	void replaceSet(CString withSet, CString toSet, CString* FileName);	
};
