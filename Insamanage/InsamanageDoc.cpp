
// InsamanageDoc.cpp: CInsamanageDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif

#include "InsamanageDoc.h"
#include "sqlite3.h"

#pragma comment(lib,"sqlite3.lib")


#ifdef _DEBUG
#define new DEBUG_NEW

#endif

// CInsamanageDoc

IMPLEMENT_DYNCREATE(CInsamanageDoc, CDocument)

BEGIN_MESSAGE_MAP(CInsamanageDoc, CDocument)
END_MESSAGE_MAP()


// CInsamanageDoc 생성/소멸

CInsamanageDoc::CInsamanageDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	
}

CInsamanageDoc::~CInsamanageDoc()
{
}

BOOL CInsamanageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CInsamanageDoc serialization

void CInsamanageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CInsamanageDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CInsamanageDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CInsamanageDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CInsamanageDoc 진단

#ifdef _DEBUG
void CInsamanageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInsamanageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CInsamanageDoc 명령
void CInsamanageDoc::CreateDB()
{
	
	sqlite3* pDB;
	char* strSQL;
	CString str, strNum, strTrno, strHotime;

	char* pErr, *pDBFile = "Da.db";

	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		AfxMessageBox(L"디비파일 오픈 실패");
		return;
	}

	str = L"디비생성.\r\n";

	strSQL = "DROP TABLE [tblData]";

	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	strSQL = "CREATE TABLE [tblData] ( \
		[Num] int(11) NOT NULL, \
		[trno] varchar(8) DEFAULT NULL, \
		[hotime] varchar(6) DEFAULT NULL \
		)";
		// MySQL 자료형으로 지정함, SQLite 자료형 확인하기.



		nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	if (nResult)
	{
		AfxMessageBox(L"테이블 생성 실패");
		sqlite3_free(&pErr);
		return;
	}

	str += L"테이블 생성.\r\n";

	strSQL = "INSERT INTO tblData (Num, trno, hotime) VALUES ( 100, 'PHONE', '10:10:10' );";

	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	if (nResult)

	{

		AfxMessageBox(L"데이터 저장 실패!");

		sqlite3_free(pErr);

		return;

	}

	str += "데이터 삽입.\r\n";



	strSQL = "SELECT * FROM tblData;";

	char **results = NULL;

	int rows, columns;

	nResult = sqlite3_get_table(pDB, strSQL, &results, &rows, &columns, &pErr);
	if (nResult)
	{
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		return;
	}
	else
	{
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			strNum = (CA2W)results[rowCtr * columns];
			strTrno = (CA2W)results[rowCtr * columns+1];
			strHotime = (CA2W)results[rowCtr * columns + 2];
			str += (strNum + L"\t" + strTrno + L"\t" + strHotime + L"\r\n");

		}

	}
	AfxMessageBox(str);
	sqlite3_free_table(results);
	sqlite3_close(pDB);

	
}


void CInsamanageDoc::DB_GetTable(char*&dbFileName, char*& sqlQuery, CListCtrl& m_dbList)
{
	m_dbList.DeleteAllItems();
	sqlite3 * pDB;
	char* strSQL;

	CString str, strTrno;

	char* pErr, *pDBFile = dbFileName;

	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패");
		return;
	}

	strSQL = sqlQuery;

	char **results = NULL;

	int rows, columns;

	nResult = sqlite3_get_table(pDB, strSQL, &results, &rows, &columns, &pErr);

	if (nResult)
	{
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		return;
	}

	CRect rect;
	m_dbList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_dbList.GetClientRect(&rect);


	for (int colCtr = 0; colCtr < columns; ++colCtr)
	{
		str = results[colCtr];
		strTrno = results[colCtr + columns];
		int a = str.GetLength(), b = strTrno.GetLength();
		//TRACE("str : %s, a: %d, strTrno : %s,  b: %d\n",results[colCtr], a,results[colCtr+columns], b);
		m_dbList.InsertColumn(colCtr, str, LVCFMT_LEFT, (a > b ? a : b) * 12);
		//m_dbList.InsertColumn(colCtr, str, LVCFMT_LEFT, str.GetLength() * 15);
	}

	for (int i = 1; i <= rows; ++i)
	{

		m_dbList.InsertItem(i, (CA2W)results[i*columns]);

	}

	for (int j = 1; j <= columns; ++j)
	{
		for (int i = 1; i <= rows; ++i)
		{
			m_dbList.SetItemText(i - 1, j, (CA2W)results[i*columns + j]);
		}
	}


	sqlite3_free_table(results);
	sqlite3_close(pDB);


}

char** CInsamanageDoc::DB_GetTable(char*&dbFileName, char*& sqlQuery, int& rows, int& columns)
{
	sqlite3 * pDB;
	char* strSQL;
	
	char* pErr, *pDBFile = dbFileName;

	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패");
		return 0;
	}

	strSQL = sqlQuery;

	char **results = NULL;

	

	nResult = sqlite3_get_table(pDB, strSQL, &results, &rows, &columns, &pErr);

	if (nResult)
	{
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		return 0;
	}
		
	
	char **returns = (char**)malloc(sizeof(char*)*(rows+1)*(columns));
		
	for (int i = 0; i <= rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (results[i*columns + j] == NULL)continue;
			int nLen = strlen(results[i*columns + j]) + 1;
			returns[i*columns+j] = (char*)calloc(nLen, sizeof(char));
			strcpy_s(returns[i*columns + j], nLen, results[i*columns + j]);
			
		}
	}
	sqlite3_free_table(results);
	sqlite3_close(pDB);

	return returns;

}

void CInsamanageDoc::DB_GetTable(char*&dbFileName, char*& sqlQuery, CListCtrl& m_dbList,CArray<CString,CString&>& m_arTxt, LVCOLUMN& Col)
{
	
	m_dbList.DeleteAllItems();
	sqlite3 * pDB;
	char* strSQL;

	CString str, strTrno;

	char* pErr, *pDBFile = dbFileName;

	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패");
		return;
	}

	strSQL = sqlQuery;

	char **results = NULL;

	int rows, columns;

	nResult = sqlite3_get_table(pDB, strSQL, &results, &rows, &columns, &pErr);

	if (nResult)
	{
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		return;
	}

	::AfxGetApp()->DoWaitCursor(1);

	CRect rect;
	m_dbList.SetExtendedStyle(LVS_EX_FULLROWSELECT|  LVS_EX_GRIDLINES);
	m_dbList.GetClientRect(&rect);
		
	Col.mask = LVCF_TEXT;

	for (int colCtr = 0; colCtr < columns; ++colCtr)
	{
		str = results[colCtr];
		strTrno = results[colCtr + columns];
		int a = str.GetLength(), b=strTrno.GetLength();
		//TRACE("str : %s, a: %d, strTrno : %s,  b: %d\n",results[colCtr], a,results[colCtr+columns], b);
		m_dbList.InsertColumn(colCtr, str, LVCFMT_LEFT, (a>b ? a : b) * 12);
		
		Col.pszText = str.GetBuffer(str.GetLength() + 1);
		Col.cchTextMax = str.GetLength() + 1;
		m_dbList.SetColumn(colCtr, &Col);
		str.ReleaseBuffer();
	}
	
	
	m_arTxt.RemoveAll();
	m_arTxt.SetSize(5000,1000);
	//int count=0;
	CString tmp;
	//for (int i = 1; i <= rows; ++i)
	//{

	//	//m_dbList.InsertItem(i, (CA2W)results[i*columns]);
	//	
	//	tmp = results[i*columns];
	//	m_arTxt.SetAtGrow(i-1, tmp);
	//	//TRACE("Setatgrow1 %d %s\n", i, results[i*columns]);
	//	count++;
	//}
	
	for (int j = 0; j < columns; ++j)
	{
		
		for (int i = 1; i <= rows; ++i)
		{
			//m_dbList.SetItemText(i - 1, j, (CA2W)results[i*columns + j]);
			//m_arTxt.SetAtGrow(i+j, results[i*columns+j]);
			
			
			tmp = results[i*columns + j];
			
			m_arTxt.SetAtGrow(i - 1 + j * rows, tmp);
			
			
			
			//TRACE("Setatgrow2 %d %s\n", j, results[i*columns+j]);
			
		}
	}

	m_dbList.SetItemCount(rows);
	m_dbList.Invalidate();
	
	sqlite3_free_table(results);
	sqlite3_close(pDB);
	
	::AfxGetApp()->DoWaitCursor(0);
}

void CInsamanageDoc::DB_CreateTable(char*&dbFileName, char*& sqlQuery)
{
	sqlite3 * pDB;
	char* strSQL;
	char* pErr, *pDBFile = dbFileName;
	
	TRACE("THREAD SAFE VALUE %d\n", sqlite3_threadsafe());

	if (sqlite3_config(SQLITE_CONFIG_SERIALIZED) == SQLITE_OK) {
		TRACE("Sqlite Serialized\n");
	}
	
	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패");
		return;
	}
	
	strSQL = sqlQuery;
	
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	if (nResult)
	{
		TRACE("쿼리 실행 실패 : %s\n\n", sqlite3_errmsg(pDB));
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return;
	}
		
	sqlite3_close(pDB);
}

void CInsamanageDoc::DB_SendQuery(char*&dbFileName, char*& sqlQuery)
{
	sqlite3 * pDB;
	char* strSQL;
	char* pErr, *pDBFile = dbFileName;
	
	if (sqlite3_config(SQLITE_CONFIG_SERIALIZED) == SQLITE_OK) {
		TRACE("Sqlite Serialized\n");
	}
	
	int nResult = sqlite3_open(pDBFile, &pDB);
	
	
	
	if (nResult)
	{
		TRACE("디비파일 오픈 실패\n");
		return;
	}

	nResult = sqlite3_exec(pDB, "PRAGMA synchronous=OFF;", NULL, NULL, NULL);
	if (nResult)
	{
		TRACE("쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
		//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return;
	}
	nResult = sqlite3_exec(pDB, "PRAGMA journal_mode=OFF;", NULL, NULL, NULL);
	if (nResult)
	{
		TRACE("쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
		//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return;
	}

	strSQL = sqlQuery;
	
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	if (nResult)
	{
		TRACE("쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return;
	}
	TRACE("쿼리 실행 : %s\n", sqlite3_errmsg(pDB));
	sqlite3_close(pDB);
		
}

void CInsamanageDoc::DB_InsertFromTxt(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2],int seekNum,int rowlen)
{
	CFile file;
	if (!file.Open(txtFileName, CFile::modeRead | CFile::typeBinary))
	{
		TRACE("파일열기 실패\n");
	}
	
	ULONGLONG fileLength = file.GetLength();
	
	BYTE* buffer = new BYTE[fileLength];
	file.Read((void*)buffer, fileLength);
	
	CMemFile memFile;
	memFile.Attach(buffer, fileLength);


	char* tmp = nullptr;

	for (int i = 0; i < fileLength; i = i + rowlen)
	{

		tmp = (char*)malloc(sizeof(char));
		CString str;
		char* sql = sqlQuery;

		char* buf = (char*)calloc(strlen(sql) + 1, sizeof(char));

		strcpy_s(buf, strlen(sql) + 1, sql);
		
		

		
		for (int j = 0; j < seekNum; j++)
		{

			loadFromTxt(str, memFile, tmp, i + seek[j][0], seek[j][1]);

			buf = (char*)realloc(buf, (_msize(tmp) + _msize(buf) + 3) * sizeof(char));


			strcat_s(buf, _msize(buf) + 1, "'");
			strcat_s(buf, _msize(buf) + 1, tmp);
			strcat_s(buf, _msize(buf) + 1, "',");


		}

		buf = (char*)realloc(buf, _msize(buf));
		strcpy_s(buf + _msize(buf) - 2, 3, ");");
		TRACE("%s\n", buf);
		DB_SendQuery(dbFileName, buf);
		buf = (char*)realloc(buf, _msize(buf));
		free(buf);
	}


	tmp = (char*)realloc(tmp, _msize(tmp));
	free(tmp);
	file.Close();
	memFile.Close();
}

void CInsamanageDoc::DB_InsertBulkFromTxt(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2], int seekNum, int rowlen)
{
	::AfxGetApp()->DoWaitCursor(1);
	sqlite3 * pDB;
	char* strSQL;
	char* pErr, *pDBFile = dbFileName;
	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패\n");
		return;
	}
	//디비파일 오픈
	
	
	
	CFile file;
	if (!file.Open(txtFileName, CFile::modeRead | CFile::typeBinary))
	{
		TRACE("파일열기 실패\n");
	}
	long fileLength = file.GetLength();
	//텍스트파일 열고 길이를 얻음

	BYTE* buffer = new BYTE[fileLength];
	file.Read((void*)buffer, fileLength);
	//메모리에 텍스트파일을 탑재할 버퍼 생성

	CMemFile memFile;
	memFile.Attach(buffer, fileLength);
	//메모리 파일 객체 생성


	TRACE("strlen sqlquery %d\n", strlen(sqlQuery));
	char* tmp = (char*)calloc(strlen(sqlQuery) + rowlen + 10, sizeof(char));
	char* buf = (char*)calloc(strlen(sqlQuery) + rowlen + 10, sizeof(char));
	//쿼리를 저장할 포인터 객체 생성
	
	nResult = SQLITE_BUSY;
	nResult = sqlite3_exec(pDB, "PRAGMA synchronous=OFF;", NULL, NULL, NULL);
	nResult = sqlite3_exec(pDB, "PRAGMA journal_mode=OFF;", NULL, NULL, NULL);
		   	  
	for (int i = 0; i < fileLength; i = i + rowlen)
	{

		strcpy_s(buf, strlen(sqlQuery) + 1, sqlQuery);

		for (int j = 0; j < seekNum; j++)
		{

			loadFromTxt(memFile, tmp, i + seek[j][0], seek[j][1]);

			/*strcat_s(buf, _msize(buf) + 1, "'");
			strcat_s(buf, _msize(buf) + 1, tmp);
			strcat_s(buf, _msize(buf) + 1, "',");*/

			strcat_s(buf, strlen(buf) + 2, "'");
			
			strcat_s(buf, strlen(buf) + strlen(tmp)+1, tmp);
			
			strcat_s(buf, strlen(buf) + 3, "',");
			

		}
		
		strcpy_s(buf + strlen(buf) - 1, 3, ");");
		



		//TRACE("쿼리 실행 : %s \n", buf);
		nResult = sqlite3_exec(pDB, buf, NULL, NULL, &pErr);

		if (nResult)
		{
			TRACE("쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
			sqlite3_close(pDB);
			return;
		}

		memset(buf, 0x00, _msize(buf));
		
	}
	
	sqlite3_close(pDB);
	TRACE("디비 종료\n", buf);
	::AfxGetApp()->DoWaitCursor(0);
	buf = (char*)realloc(buf, _msize(buf));
	free(buf);

	tmp = (char*)realloc(tmp, _msize(tmp));
	free(tmp);
	file.Close();
	
	buffer = memFile.Detach();
	delete buffer;
}

void CInsamanageDoc::DB_InsertBulkFromTxtLine(char*&dbFileName, char*& sqlQuery, CString txtFileName, int seek[][2], int seekNum, int rowlen)
{
	::AfxGetApp()->DoWaitCursor(1);
	sqlite3 * pDB;
	char* strSQL;
	char* pErr, *pDBFile = dbFileName;
	int nResult = sqlite3_open(pDBFile, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패\n");
		return;
	}
	//디비파일 오픈



	CFile file;
	if (!file.Open(txtFileName, CFile::modeRead | CFile::typeBinary))
	{
		TRACE("파일열기 실패\n");
	}
	long fileLength = file.GetLength();
	//텍스트파일 열고 길이를 얻음

	BYTE* buffer = new BYTE[fileLength];
	file.Read((void*)buffer, fileLength);
	//메모리에 텍스트파일을 탑재할 버퍼 생성

	CMemFile memFile;
	memFile.Attach(buffer, fileLength);
	//메모리 파일 객체 생성


	//TRACE("strlen sqlquery %d\n", strlen(sqlQuery));
	char* tmp = (char*)calloc(strlen(sqlQuery) + rowlen + 10, sizeof(char));
	char* buf = (char*)calloc(strlen(sqlQuery) + rowlen + 10, sizeof(char));
	//쿼리를 저장할 포인터 객체 생성

	nResult = SQLITE_BUSY;
	nResult = sqlite3_exec(pDB, "PRAGMA synchronous=OFF;", NULL, NULL, NULL);
	nResult = sqlite3_exec(pDB, "PRAGMA journal_mode=OFF;", NULL, NULL, NULL);

	char* check = (char*)malloc(sizeof(char)*1);
	int pre = 0;
	int	after = 0;
	for (int i = 0; i <= fileLength; i++)
	{
		memFile.Seek(i, CFile::begin);
		memFile.Read(check, 1);
				
		if ( check[0] == '\n' || i == fileLength)
		{
			after = pre;
			pre = i + 1;

			strcpy_s(buf, strlen(sqlQuery) + 1, sqlQuery);

			for (int j = 0; j < seekNum; j++)
			{

				loadFromTxt(memFile, tmp, after + seek[j][0], pre - after - seek[j][0] < seek[j][1] ? pre - after - seek[j][0] : seek[j][1]);

				/*strcat_s(buf, _msize(buf) + 1, "'");
				strcat_s(buf, _msize(buf) + 1, tmp);
				strcat_s(buf, _msize(buf) + 1, "',");*/

				strcat_s(buf, strlen(buf) + 2, "'");

				strcat_s(buf, strlen(buf) + strlen(tmp) + 1, tmp);

				strcat_s(buf, strlen(buf) + 3, "',");


			}

			strcpy_s(buf + strlen(buf) - 1, 3, ");");




			//TRACE("쿼리 실행 : %s \n", buf);
			nResult = sqlite3_exec(pDB, buf, NULL, NULL, &pErr);

			if (nResult)
			{
				TRACE("쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
				sqlite3_close(pDB);
				return;
			}

			memset(buf, 0x00, _msize(buf));
		}
	}

	sqlite3_close(pDB);
	TRACE("디비 종료\n", buf);
	::AfxGetApp()->DoWaitCursor(0);
	buf = (char*)realloc(buf, _msize(buf));
	free(buf);

	tmp = (char*)realloc(tmp, _msize(tmp));
	free(tmp);
	file.Close();
	buffer = memFile.Detach();
	delete buffer;
	
}



char* CInsamanageDoc::DB_ConCat(char* format, ...)
{ 
	
	int iLen = 0;
	va_list arglist;
	va_start(arglist, format);
			
	/*char* temp= nullptr;
	int count = 0;
	do
	{
		temp = va_arg(arglist, char*);
		iLen += temp != NULL ? strlen(temp) : 0;
		count++;
	}while (temp != nullptr);

	
	char* pszTemp = new char[iLen+strlen(format)+count+2];*/
	
	iLen = _vscprintf(format, arglist) + 1;
	
	char * pszTemp = new char[iLen];
	memset(pszTemp, 0, sizeof(char)*iLen);

	vsprintf_s(pszTemp,iLen, format , arglist);
	
	//TRACE("psz Temp : %s, iLen : %d\n", pszTemp, iLen);

	va_end(arglist);
	
	return pszTemp;
}

void CInsamanageDoc::loadFromTxt(CString &str, CFile &file, char*& tmp, long filepointer, int charlength)
{
	if (_msize(tmp) - 1 != charlength)
	{
		char* old = tmp;
		tmp = (char*)realloc(tmp, sizeof(char) * charlength);
		memset(tmp, 0x00, charlength + 1);

	}

	file.Seek(filepointer, CFile::begin);
	file.Read(tmp, charlength);
	str = tmp;

}

void CInsamanageDoc::loadFromTxt(CMemFile &file, char*& tmp, long filepointer, int charlength)
{
	memset(tmp, 0x00, _msize(tmp));
	file.Seek(filepointer, CMemFile::begin);
	file.Read(tmp, charlength);
	//TRACE("loadfrom txt len %d memsize %d : %s\n",strlen(tmp), _msize(tmp),tmp);
}

char* CInsamanageDoc::StringToChar(CString str)
{
	char *szStr = NULL;
#if defined(UNICODE) || defined(_UNICODE)
	int nLen = str.GetLength() + 1;
	TCHAR *tszTemp = NULL;
	tszTemp = new TCHAR[nLen];
	memset(tszTemp, 0x00, nLen * sizeof(TCHAR));
	_tcscpy_s(tszTemp, nLen, str);
	// Get size (실제사용되는바이트사이즈)
	int nSize = WideCharToMultiByte(CP_ACP, 0, tszTemp, -1, NULL, NULL, NULL, NULL);
	szStr = new char[nSize];
	memset(szStr, 0x00, nSize);
	WideCharToMultiByte(CP_ACP, 0, tszTemp, -1, szStr, nSize, NULL, NULL);
	if (tszTemp)
	{
		delete[] tszTemp;
		tszTemp = NULL;
	}
#else
	int nLen = str.GetLength() + 1;
	szStr = new char[nLen];
	memset(szStr, 0x00, nLen);
	strcpy(szStr, str);
#endif
	return szStr;
}