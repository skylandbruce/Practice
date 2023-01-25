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

    // �������̵� �Լ�
//////////////////////////////////////////////
protected:
virtual	void init();
virtual	void initService();

protected:
	// Root �� ��� ����
	ViewFileDialog* BrowseFile;
	bool setExeFile(void);
	Entity* getExeFile(int index);
	ViewBitmapButton* getBitmapButton(Entity* entity, int index);
	MetaInfo* getExeFile();


virtual	void updateRoot(CString path);
public:
	MetaInfo* getRootPath(void);


	// TreeList ����
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
