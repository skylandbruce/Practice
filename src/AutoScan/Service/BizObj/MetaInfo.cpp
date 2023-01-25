#include "StdAfx.h"
#include "MetaInfo.h"



MetaInfo::MetaInfo(void)
{
}

MetaInfo::~MetaInfo(void)
{

}

MetaInfo::MetaInfo(CString type) 
{
	metaObjName = type;
}

	CString MetaInfo::getMetaTitle(){return metaTitle;}
	CString MetaInfo::getMetaFullPathName(){return metaFullPathName;}
	CString MetaInfo::getMetaPath(){return metaPath;}
	CString MetaInfo::getMetaRelativePath(){return metaRelativePath;}
	CString MetaInfo::getMetaDirName(){return metaDirName;}
	CString MetaInfo::getMetaFileName(){return metaFileName;}
	CString MetaInfo::getMetaFilter(){return metaFilter;}
	CString MetaInfo::getMetaDrive(){return metaDrive;}
	CString MetaInfo::getMetaObjName(){return metaObjName;}

// aaa\bbb\ccc.ext
	void MetaInfo::setMetaFullPathName(CString fullpathname)
	{
		int index;
		CString Path;
		CString FileName;

		metaFullPathName=fullpathname;

		index=fullpathname.ReverseFind(_T('\\'));
		Path=fullpathname.Left(index+1);
		setMetaPath(Path);

		index=fullpathname.GetLength()-index-1;
		FileName=fullpathname.Right(index);
		setMetaFileName(FileName);
	}
// aaa\bbb\ 
	void MetaInfo::setMetaPath(CString path)
	{
		int index;
		CString DirName;
		
		metaPath=path;

		path.TrimRight(_T('\\'));
		index=path.ReverseFind(_T('\\'));
		index=path.GetLength()-index-1;
		DirName=path.Right(index);
		setMetaDirName(DirName);

		index=path.Find(_T('\\'),0);
		setMetaDrive(path.Left(index+1));
	}

	void MetaInfo::setMetaRelativePath(CString basepath)
	{
		CString RelativePath;
		int relativeLength;

//		RootPath=metaPath;
		relativeLength=basepath.GetLength()-metaPath.GetLength();

		if(relativeLength>0)
		{		
			basepath=basepath.Right(relativeLength);
			for(int start=0; (start!= -1) && start<relativeLength ;start++)		 
			{
				start=basepath.Find(_T("\\"),start);
				RelativePath+=_T("..\\");
			}
		}
		else
		{
			RelativePath=metaPath.Right(abs(relativeLength));
			RelativePath=_T(".\\")+RelativePath;
		}

		metaRelativePath=RelativePath;
	}
// bbb  
	void MetaInfo::setMetaDirName(CString dirname)
	{metaDirName=dirname;}

	void MetaInfo::setMetaFileName(CString filename)
	{
		int index;
		CString Filter;

		metaFileName=filename;

		index=filename.ReverseFind(_T('.'));
		if(index!=-1) 
		{
		index=filename.GetLength()-index-1;
		Filter=filename.Right(index);
		}
		setMetaFilter(Filter);
		
	}

	void MetaInfo::setMetaFilter(CString filter)
	{metaFilter=filter;}

	void MetaInfo::setMetaDrive(CString drive)
	{metaDrive=drive;};



	