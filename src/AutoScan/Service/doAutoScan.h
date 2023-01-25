#pragma once
#include "Framework.h"
//#include "ViewBrowseFile.h"
#include "ViewBrowseFolder.h"
//#include "ViewFolderDialog.h"
#include "ViewFileDialog.h"

class doAutoScan : public Framework
{
protected:
	MetaInfo* mBaseMeta;


public:
	doAutoScan(void);
	~doAutoScan(void);

    // 오버라이딩 함수
//////////////////////////////////////////////
protected:
virtual	void init();
virtual	void initService();

protected:
	// Makefile(*.mak) 의 위치를 지정한다
//	ViewBrowseFile *BrowseFile;
	ViewFileDialog* BrowseFile;
	bool setMakeFile(void);
	// View의 정보를 MetaFile에 업데이트하고 FullPathName을 return함
	void updateMakeFile(void);
public:
	MetaInfo* getMakeFile(void);

protected:
	// Root 의 경로 지정
	ViewBrowseFolder* BrowseFolder;
//	ViewFolderDialog* BrowseFolder;
	bool setRoot(void);
virtual	void updateRoot(void);
public:
	MetaInfo* getRootPath(void);


	// TreeList 생성
	void getTreeList();

protected:
	void openMIN(void);
	void saveMIN(Entity* prototype);
	void saveIncludeMIN(Entity* prototype);
	void openIncludeMIN(void);
public:
	void createConfigure(void);
};
