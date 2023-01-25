#pragma once

class MetaInfo {
protected:
	CString metaTitle;
	CString metaFullPathName;
	CString metaPath;
	CString metaRelativePath;
	CString metaDirName;
	CString metaFileName;
	CString metaFilter;
	CString metaDrive;
	CString metaObjName;
public:
	MetaInfo(void);
	MetaInfo(CString type);
	~MetaInfo(void);

	CString getMetaTitle();
	CString getMetaFullPathName();
	CString getMetaPath();
	CString getMetaRelativePath();
	CString getMetaDirName();	
	CString getMetaFileName();		
	CString getMetaFilter();
	CString getMetaDrive();
	CString getMetaObjName();

	void setMetaFullPathName(CString fullpathname);
	void setMetaPath(CString path);
	void setMetaRelativePath(CString basepath);
	void setMetaDirName(CString dirname);	
	void setMetaFileName(CString filename);	
	void setMetaFilter(CString filter);
	void setMetaDrive(CString drive);
};
