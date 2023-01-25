#include "StdAfx.h"
#include "UtilString.h"

UtilString::UtilString(void)
{
}

UtilString::~UtilString(void)
{
}

// FileNamme (aaa.c) 를 FileName(aaa) 와 Ext(c) 로 분리
void UtilString::splitFileName(CString* FileName, CString* Ext)
{
	int index;
	CString Filter;

	index=FileName->ReverseFind(_T('.'));
	if(index==-1) return; 

	*Ext=(FileName->Right(FileName->GetLength()-index-1));
	FileName->Delete(index,FileName->GetLength()-index);	
}

// *를 포함한 fullset 이 subset을 포함 하는지 판별
bool UtilString::isSubSet(CString fullset, CString subset)
{
	int forIndex;
	int revIndex;
	if(fullset.Compare(_T("*")) == 0) return true;

	forIndex=fullset.Find(_T('*'));
	revIndex=fullset.ReverseFind(_T('*'));
	// s
	if(forIndex==-1 && revIndex==-1)
	{
		if(subset.Compare(fullset)==0) return true;
		return false;
	}

	fullset.Remove(_T('*'));	
	// s*
	if(forIndex==revIndex && revIndex==fullset.GetLength())
	{
		forIndex=subset.Find(fullset);
		if(forIndex==-1 || forIndex!=0) return false;
		if(fullset.GetLength() < subset.GetLength() ) return true;
	}
	// *s
	else if(forIndex==revIndex && forIndex==0)
	{
		revIndex=subset.Find(fullset);
		if(revIndex==-1 || revIndex==0) return false;
		if(revIndex+fullset.GetLength() == subset.GetLength()) return true;
	}
	// *s*
	else if(forIndex!=revIndex)
	{
		forIndex=subset.Find(fullset,1);
		if(forIndex==-1 || forIndex+fullset.GetLength() == subset.GetLength()) return false;
		return true;		
	}
	return false;
}

// aaa*.c => ccc*.c / cc*.cpp
// *bbb.c => *ccc.c / *cc.cpp
void UtilString::replaceSet(CString withSet, CString toSet, CString* FileName)
{

	CString tokenWithStr;
	CString tokenToStr;
	int tokenWithPos=0;
	int tokenToPos=0;

	// 검색글과 변환글이 모두 비어 있으면 리턴
	if(withSet.IsEmpty()==true || toSet.IsEmpty()==true ) return;

	// 검색글과 변환글에 *가 없으면 변환글로 파일네일 대체
	if(withSet.Find(_T("*"))==-1 && toSet.Find(_T("*"))==-1)
	{
		*FileName=toSet;
		return;
	}

	// * 포함시 대체
	// 검색글과 변환글의 포맷이 다를때 오류 발생 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	tokenWithStr=withSet.Tokenize(_T("*"), tokenWithPos);
	tokenToStr=toSet.Tokenize(_T("*"), tokenToPos);
	while(tokenWithStr.IsEmpty()==false && tokenToStr.IsEmpty()==false) 
	{
		FileName->Replace(tokenWithStr, tokenToStr);

		tokenWithStr=withSet.Tokenize(_T("*"), tokenWithPos);
		tokenToStr=toSet.Tokenize(_T("*"), tokenToPos);
	}

}

CString UtilString::TrimToken(CString str, CString token, bool includeToken)
{

	return NULL;
}

CString UtilString::reverseTrimToken(CString str, TCHAR token, bool includeToken)
{
	int index;

	index=str.ReverseFind(token);	
	if(index==-1)
		return str;

	if(includeToken == true)
		str.Delete(index, str.GetLength()-index);
	else
	{
		if(index!=str.GetLength()-1)
			str.Delete(index+1, str.GetLength()-index-1);
	}
	return str;
}