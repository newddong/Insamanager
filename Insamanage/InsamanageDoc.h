
// InsamanageDoc.h: CInsamanageDoc 클래스의 인터페이스
//


#pragma once


class CInsamanageDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CInsamanageDoc() noexcept;
	DECLARE_DYNCREATE(CInsamanageDoc)

// 특성입니다.
public:
	void DB_GetTable(char*&dbFileName, char*& sqlQuery, CListCtrl& m_dbList);
	void DB_GetTable(char*&dbFileName, char*& sqlQuery, CListCtrl& m_dbList, CArray<CString, CString&>& m_arTxt, LVCOLUMN& Col);
	char** DB_GetTable(char*&dbFileName, char*& sqlQuery, int& rows, int& columns);
	void DB_CreateTable(char*&dbFileName, char*& sqlQuery);
	void DB_SendQuery(char*&dbFileName, char*& sqlQuery);
	void loadFromTxt(CString &str, CFile &file, char*& tmp, long filepointer, int charlength);
	void loadFromTxt(CMemFile &file, char*& tmp, long filepointer, int charlength);
	void DB_InsertFromTxt(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2],int seekNum, int rowlen);
	void DB_InsertBulkFromTxt(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2], int seekNum, int rowlen);
	void DB_InsertBulkFromTxtLine(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2], int seekNum, int rowlen);
	char* StringToChar(CString str);
	char* DB_ConCat(char* format, ...);
	// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CInsamanageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void CreateDB();

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
