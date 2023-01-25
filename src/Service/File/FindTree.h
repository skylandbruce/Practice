#pragma once
#include "Service.h"

#include "FindFiles.h"
#include "MakeTree.h"

class FindTree : public Service
{
protected:
    MakeTree* mMakeTree;
	FindFiles* mFindFiles;
public:
	FindTree(void);
	~FindTree(void);

//	void getTree(void);
	void getTree(Entity* prototype);
//	void recursiveTree(CString path, CString filter);
	void recursiveTree(CString path, Entity* prototype);
};