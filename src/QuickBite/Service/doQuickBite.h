#pragma once
#include "Framework.h"
#include "ViewFileDialog.h"
#include "UtilString.h"
#include "ViewBitmapButton.h"

#define DATAFILE _T("QUICKDATAFILE.DAT")

class doQuickBite : public Framework
{
protected:
	CString ExeFilePath;
	CPtrArray buttonArray;
	CPtrArray* EntitySet;
	bool isBasic;
	int validButtonCount;

	CString DataPathFile;
public:
	doQuickBite(void);
	~doQuickBite(void);

    // 오버라이딩 함수
//////////////////////////////////////////////
protected:
virtual	void init();
virtual	void initService();

protected:
	// Root 의 경로 지정
	ViewFileDialog* BrowseFile;
	bool setExeFile(void);
	Entity* getExeFile(int index);
	ViewBitmapButton* getBitmapButton(Entity* entity, int index);
	MetaInfo* getExeFile();


virtual	void updateRoot(CString path);
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
	void doConfigure(CWnd* pParentWnd);
	void doAction();

	void doExtend(CWnd* pParentWnd);
	void doBasic();
	void addNewButton(CWnd* pParentWnd);
};
