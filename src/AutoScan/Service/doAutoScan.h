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

    // �������̵� �Լ�
//////////////////////////////////////////////
protected:
virtual	void init();
virtual	void initService();

protected:
	// Makefile(*.mak) �� ��ġ�� �����Ѵ�
//	ViewBrowseFile *BrowseFile;
	ViewFileDialog* BrowseFile;
	bool setMakeFile(void);
	// View�� ������ MetaFile�� ������Ʈ�ϰ� FullPathName�� return��
	void updateMakeFile(void);
public:
	MetaInfo* getMakeFile(void);

protected:
	// Root �� ��� ����
	ViewBrowseFolder* BrowseFolder;
//	ViewFolderDialog* BrowseFolder;
	bool setRoot(void);
virtual	void updateRoot(void);
public:
	MetaInfo* getRootPath(void);


	// TreeList ����
	void getTreeList();

protected:
	void openMIN(void);
	void saveMIN(Entity* prototype);
	void saveIncludeMIN(Entity* prototype);
	void openIncludeMIN(void);
public:
	void createConfigure(void);
};
