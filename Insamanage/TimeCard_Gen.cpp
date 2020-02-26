
#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "TimeCard_Gen.h"
#include "sqlite3.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT readFile(LPVOID pParam);

IMPLEMENT_DYNCREATE(TimeCard_Gen, CFormView)

TimeCard_Gen::TimeCard_Gen() :CFormView(TimeCard_Gen::IDD)
{
}


TimeCard_Gen::~TimeCard_Gen()
{
}

void TimeCard_Gen::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ERPFILES, m_erpFileList);
	DDX_Control(pDX, IDC_ERP, m_erpList);
}


BEGIN_MESSAGE_MAP(TimeCard_Gen, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ERP_PATH, &TimeCard_Gen::OnClickedPath)
	ON_BN_CLICKED(IDC_ERP_LOAD, &TimeCard_Gen::OnClickedLoad)
	ON_BN_CLICKED(IDC_ERP_GEN, &TimeCard_Gen::OnClickedGen)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ERPFILES, GetDispInfo)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ERP, GetDispInfo)
END_MESSAGE_MAP()

#ifdef _DEBUG
void TimeCard_Gen::AssertValid() const
{
	CFormView::AssertValid();
}

void TimeCard_Gen::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void TimeCard_Gen::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void TimeCard_Gen::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL TimeCard_Gen::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void TimeCard_Gen::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void TimeCard_Gen::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void TimeCard_Gen::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_TimeCard_Gen);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void TimeCard_Gen::OnClickedPath()
{
			
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("ERP 파일이 저장되어있는 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);               // 파일경로 읽어오기
	
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("erpFilePath"), szBuffer);
	   
}

void TimeCard_Gen::OnClickedLoad()
{
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	m_erpFileList.DeleteAllItems();
	while (m_erpFileList.DeleteColumn(0));
	m_arTxts.RemoveAll();
	
	m_erpFileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	LVCOLUMN Col;
	Col.mask = LVCF_TEXT;

	m_erpFileList.InsertColumn(0, _T("파일명"), LVCFMT_LEFT, 150);
	Col.pszText = _T("file");
	//Col.cchTextMax = str.GetLength() + 1;
	m_erpFileList.SetColumn(0, &Col);


	
	CFileFind finder;
	CString path = AfxGetApp()->GetProfileStringW(_T("Settings"), _T("erpFilePath"));
	//TRACE(_T("%s\n"), path+_T("\\*.*"));

	BOOL bFind = finder.FindFile(path + _T("\\*.*"));

	while (bFind)
	{
		bFind = finder.FindNextFile();
		if (finder.IsDirectory() || finder.IsDots())continue;
		m_arTxts.Add(finder.GetFileName());
		
	}
			
	
	m_erpFileList.SetItemCount(m_arTxts.GetCount());
	m_erpFileList.Invalidate();


	//=====
	m_erpList.DeleteAllItems();
	while (m_erpList.DeleteColumn(0));
	m_arTxts2.RemoveAll();

	m_erpList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	/*m_erpList.InsertColumn(0, _T("파일명"), LVCFMT_LEFT, 150);
	m_erpList.InsertColumn(1, _T("시간"), LVCFMT_LEFT, 150);
	m_erpList.InsertColumn(2, _T("사원번호"), LVCFMT_LEFT, 150);*/
	
	/*Col.pszText = _T("Date");
	m_erpList.SetColumn(0, &Col);
	Col.pszText = _T("Time");
	m_erpList.SetColumn(1, &Col);
	Col.pszText = _T("id");
	m_erpList.SetColumn(2, &Col);*/


	m_erpList.SetItemCount(m_arTxts2.GetCount());
	char* query = "SELECT * FROM FROMERP;";
	char* file = "Database.db";

	pDoc->DB_GetTable(file, query, m_erpList, m_arTxts2, Col);


	m_erpList.Invalidate();
	
	UpdateData(FALSE);
	finder.Close();

}

void TimeCard_Gen::OnClickedGen()
{
	UINT setting = AfxGetApp()->GetProfileIntW(_T("Settings"), _T("tableGen"), 0);
	
	CString lastFileRead = AfxGetApp()->GetProfileStringW(_T("Settings"), _T("lasterpFileRead"));
	



	char *fileName = "Database.db";
	char *query = "CREATE TABLE [FROMERP] ( \
			[DATE] varchar(10) DEFAULT NULL, \
			[TIME] varchar(10) DEFAULT NULL, \
			[ID] varchar(10) DEFAULT NULL \
			)";
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char* lst = pDoc->StringToChar(lastFileRead);
	int lastFileReadNum = atoi(lst);

	if (setting != 1) {
		
		pDoc->DB_CreateTable(fileName, query);
		AfxGetApp()->WriteProfileInt(_T("Settings"), _T("tableGen"), 1);
		TRACE("%d 실행함\n", setting);
	}
	else {
		TRACE("테이블이 이미 생성됨\n");
	}

	CFileFind finder;
	CString path = AfxGetApp()->GetProfileStringW(_T("Settings"), _T("erpFilePath"));
	BOOL bFind = finder.FindFile(path + _T("\\*.*"));
	CFile erpFile;

	while (bFind)
	{
		bFind = finder.FindNextFile();
		char* fileTitle = pDoc->StringToChar(finder.GetFileTitle());
		if (atoi(fileTitle) <= lastFileReadNum)continue;

		if (finder.IsDirectory() || finder.IsDots())continue;
		

		if (!erpFile.Open(finder.GetFilePath(), CFile::modeRead | CFile::typeBinary))
		{
			TRACE("ERP FILE OPEN ERROR\n");
		}
		
		CMemFile memFile;
		int erpFileLength = erpFile.GetLength();
		BYTE* buf = new BYTE[erpFileLength];
		erpFile.Read(buf, erpFileLength);
		memFile.Attach(buf, erpFileLength);
		
		TRACE(_T("%s\n"), finder.GetFilePath());
		int pre = 0, after = 0;
		char* mbuf = new char[83];
		char* date = new char[9];
		char* time = new char[7];
		char* id = new char[9];
		char* sql;

		for (int i = 0; i < erpFileLength; i++) {
			if(buf[i] == '\n')
			{
				pre = after;
				after = i+1;
				//TRACE("pre : %d, after : %d, length : %d\n", pre, after, after-pre);
				if (after - pre - 2 < 24)continue;
				memFile.Seek(pre, CFile::begin);
				
				memFile.Read(mbuf, after-pre-2 > 24 ? 24 : after-pre-2);
				//memFile.Read(mbuf, after - pre-2);
				mbuf[after - pre - 2 > 24 ? 24 : after - pre - 2] = '\0';
				memcpy_s(date, 8, mbuf, 8);
				date[8] = 0x00;
				memcpy_s(time, 6, mbuf+9, 6);
				time[6] = 0x00;
				memcpy_s(id, 8, mbuf + 16, 8);
				id[8] = 0x00;

				//mbuf[after - pre - 1] = 0x00;
				//TRACE("wbuf : %s , date : %s , time : %s , id : %s \n", mbuf, date, time, id);
				query = "INSERT INTO FROMERP (DATE, TIME, ID) VALUES (";
				sql = pDoc->DB_ConCat("%s '%s', '%s', '%s');",query, date, time, id);
				TRACE("sql : %s\n", sql);
				pDoc->DB_SendQuery(fileName, sql);
				delete sql;
			}
			
		}
				
		
		buf = memFile.Detach();
		delete buf, mbuf, date, id, time, fileTitle;
		erpFile.Close();
	}
	
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("lasterpFileRead"), finder.GetFileTitle());
	finder.Close();
	
}

void TimeCard_Gen::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int erpitemCount = m_erpList.GetItemCount();

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		//TRACE("BeforeSwitch\n");
		//lstrcpy(pItem->pszText, rLabel);


		if (IDC_ERPFILES == pNMHDR->idFrom) {

			TRACE("id : %d,  item : %d\n", pNMHDR->idFrom, pItem->iItem);
			rLabel = m_arTxts.ElementAt(pItem->iItem);

			lstrcpy(pItem->pszText, rLabel);
			
			
			

			
		}
		if (IDC_ERP == pNMHDR->idFrom) {

			rLabel = m_arTxts2.ElementAt(pItem->iItem + pItem->iSubItem * erpitemCount);

			lstrcpy(pItem->pszText, rLabel);
		}



		
		
		
		
		//TRACE("iItem : %d, iSubItem : %d\n", pItem->iItem, pItem->iSubItem);

		//switch (pItem->iSubItem)
		//{
		//case 0:
		//	
		//	lstrcpy(pItem->pszText, rLabel);
		//	break;
		//case 1:
		//	//lstrcpy(pItem->pszText, rLabel);
		//	wsprintf(pItem->pszText, L"두번째%s", rLabel);
		//	break;
		///*default:
		//	
		//	ASSERT(0);
		//	
		//	break;*/
		//}

	}


	*pResult = 0;
}


CArray<CString, CString&> arr;

struct tinformation {
	CArray<CString, CString&>* lparr;
	int count;
	int max_count;
	int key;
	CInsamanageDoc* pDoc;
	sqlite3* pDB;
	char *pErr;
}info;

bool dbopen;

void TimeCard_Gen::OnClickedButton()
{
	tinformation* in = &info;
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	in->pDoc = pDoc;

	if (sqlite3_config(SQLITE_CONFIG_MULTITHREAD) == SQLITE_OK) {
		TRACE("Sqlite Serialized\n");
	}

	TRACE("threadsafe %d\n", sqlite3_threadsafe());

	char *fileName = "test.db";
	
	int nResult = 0;
	
	
	nResult = sqlite3_open(fileName, &in->pDB);
	
	if (nResult)
	{
		TRACE("디비파일 오픈 실패");
		return;
	}
	
	
	
	char *query = "CREATE TABLE [TEST] ( \
			[AVAL] INTEGER PRIMARY KEY, \
			[DATE] varchar(10) DEFAULT NULL \
			)";
	
	nResult = sqlite3_exec(in->pDB, query, NULL, NULL, &in->pErr);

	if (nResult)
	{
		TRACE("쿼리 실행 실패 : %s\n\n", sqlite3_errmsg(in->pDB));
		AfxMessageBox(CString(sqlite3_errmsg(in->pDB)));
		//sqlite3_free(&pErr);
		//sqlite3_close(in->pDB);
		//return;
	}
	
	
	in->key = 0;
	int count = 2;

	TRACE("생성할 스레드 수 : %d개\n", count);
	
	for (int i = 0; i < count; i++) {
		
		::AfxBeginThread(readFile, in);
			
	}
		
	sqlite3_close(in->pDB);
}


UINT readFile(LPVOID pParam) 
{
	tinformation* in = (tinformation*)pParam;
	
	char *fileName = "test.db";
	
	sqlite3 * pDB;
	char* strSQL;
	char* pErr;

	if (sqlite3_config(SQLITE_CONFIG_MULTITHREAD) == SQLITE_OK) {
		TRACE("Sqlite Serialized\n");
	}

	int nResult = sqlite3_open(fileName, &pDB);

	if (nResult)
	{
		TRACE("디비파일 오픈 실패\n");
		return 0;
	}

	nResult = sqlite3_exec(pDB, "PRAGMA synchronous=OFF;", NULL, NULL, NULL);
	if (nResult)
	{
		TRACE("싱크 오프 쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
		//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return 0;
	}
	nResult = sqlite3_exec(pDB, "PRAGMA journal_mode=OFF;", NULL, NULL, NULL);
	if (nResult)
	{
		TRACE("저날 오프 쿼리 실행 실패 : %s\n", sqlite3_errmsg(pDB));
		//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		sqlite3_close(pDB);
		return 0;
	}


	int threadId = AfxGetThread()->m_nThreadID;
	
	TRACE("%8x 스레드 실행\n",threadId);
	
	tinformation* info = (tinformation*)pParam;
	
	
	int key = info->key;
	info->key += 10000000;
	int count = info->key;

	strSQL = "BEGIN CONCURRENT";
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);
	if (nResult)
	{
		TRACE("%8x : %s 컨커런트 쿼리 실행 실패 : %s\n", threadId, strSQL, sqlite3_errmsg(pDB));
		//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		//sqlite3_free(&pErr);
		//sqlite3_close(pDB);
		//return;
	}


	char* query = "INSERT INTO TEST (AVAL, DATE) VALUES (";
	
	
	
	for (int i = 0; i < 20; i++) {
		
		

		
		strSQL = in->pDoc->DB_ConCat("%s %d, '%s');", query, count++, "2018");
		TRACE("%8x : %s 쿼리 시도\n", threadId, strSQL);
		nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

		if (nResult)
		{
			TRACE("%8x : %s 쿼리 실행 실패 : %s\n",threadId, strSQL, sqlite3_errmsg(pDB));
			//AfxMessageBox(CString(sqlite3_errmsg(pDB)));
			//sqlite3_free(&pErr);
			//sqlite3_close(pDB);
			//return;
		}
		else
		{
			TRACE("%8x : %s 쿼리 실행 성공: %s\n", threadId, strSQL, sqlite3_errmsg(pDB));
		}
	}
	
	

	sqlite3_close(pDB);

	
	TRACE("%8x 스레드 종료\n", threadId);
	return 0;
}