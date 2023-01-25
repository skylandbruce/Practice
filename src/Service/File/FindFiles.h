#pragma once
#include "Service.h"


class FindFiles : public Service
{
protected:   
	CMapStringToOb* EntitySetPool;
	CStringList* FileList;
	CStringList* DirList;
	// directory ����Ʈ
	void getSelfList(CString path, CStringList* list, Entity* fileProto);


/*
	void getSelfList(Entity* Instance, CString path, DWORD attributefilter, Entity* prototye);
	void getSelfList(CStringList* list, CString path, DWORD attributefilter,  CString filter);
*/
public:
	FindFiles(void);
	~FindFiles(void);

	CStringList* getDirList(CString path, Entity* fileProto);
	int getFileList(CString path, DWORD attribute, Entity* prototype);

	// Dir StringList �� return��
//	CStringList* getPathList(CString path, CString filter);
//	CStringList* getPathList(CString path, Entity* ptototype);

	// Kit���� ���ǵ� ��� StringList�� return��
//	CStringList* openFiles(CString name, CString condition);

	friend bool EntityKit::isValidFile(Entity* prototype, CString fileName);
	friend CString UtilString::reverseTrimToken(CString str, TCHAR token, bool includeToken);
};