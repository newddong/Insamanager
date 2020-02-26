#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Prog_dbmanage.h"

#include "sqlite3.h"
#pragma comment(lib,"sqlite3.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Prog_dbmanage, CFormView)

Prog_dbmanage::Prog_dbmanage() :CFormView(Prog_dbmanage::IDD)
{
}


Prog_dbmanage::~Prog_dbmanage()
{
}

void Prog_dbmanage::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROG_DBLIST, m_dbList);
	DDX_Control(pDX, IDC_TABLESELECT, m_dbSelect);
	DDX_Control(pDX, IDC_SQLQUERY, m_ctrlSqlEdit);
}


BEGIN_MESSAGE_MAP(Prog_dbmanage, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO,IDC_PROG_DBLIST, GetDispInfo)
	ON_BN_CLICKED(IDC_GENDB, &Prog_dbmanage::OnBnClickedGendb)
	ON_BN_CLICKED(IDC_DBVIEW, &Prog_dbmanage::OnClickedDbview)
	ON_BN_CLICKED(IDC_TEXTVIEW, &Prog_dbmanage::OnBnClickedTextview)
	ON_CBN_SELCHANGE(IDC_TABLESELECT, &Prog_dbmanage::OnSelchangeTableselect)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Prog_dbmanage::AssertValid() const
{
	CFormView::AssertValid();
}

void Prog_dbmanage::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Prog_dbmanage::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Prog_dbmanage::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Prog_dbmanage::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Prog_dbmanage::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Prog_dbmanage::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	/*char* colNames[] = { "fff","sss" };
	CString header;
	CRect rect;
	m_dbList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_dbList.GetClientRect(&rect);
	header = colNames[0];
	
	m_dbList.InsertColumn(0, header, LVCFMT_LEFT, 60);
	
	m_dbList.InsertColumn(1, header, LVCFMT_RIGHT, 60);*/

	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));
	init_dbSelect();
	
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Prog_dbmanage::OnSize(UINT nType, int cx, int cy)
{
	
	CFormView::OnSize(nType, cx, cy);
	
	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_PROG_DBLIST);
	if (lst == NULL) {
		//AfxMessageBox(L"리스트 없음");
		return;
	}
	
	lst->SetWindowPos(NULL, 0, 0, cx-100, cy-100, SWP_NOMOVE|SWP_NOZORDER);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


//========DB 조회부분 =================


void Prog_dbmanage::genDbfromTxt()//텍스트파일에서 컨트롤로 바로 표시
{
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_PROG_DBLIST);
	lst->ModifyStyleEx(LVS_OWNERDATA, 0);
	m_dbList.DeleteAllItems();
	
	
	UpdateData(TRUE);

	genColumns();
	
	CFile file;
	file.Open(_T("g1101.txt"), CFile::modeRead|CFile::typeBinary);

	m_dbList.SetItemCount(int(80941 / 373));

	int seek[30][2]/*filepointer,charlength*/ = { /*이름*/{8,8},/*주민번호*/{16,13},/*주소*/{29,72},
	/*전화번호*/{101,13},/*빈칸*/{114,49},/*전화번호*/{163,12},/*급여구분*/{175,1},
	/*입사경위*/{176,1},/*코드*/{177,1},/*코드2*/{180, 1},/*입사일자*/{181, 8},
	/*발령일자*/{ 189, 8 },/*승진일자*/{ 197, 8 },/*휴직일자*/{ 205, 8 },
	/*복직일자*/{ 213, 8 },/*퇴직일자*/{ 221, 8 },/*부서*/{ 229, 4 },
	/*직급*/{ 235, 3 },/*코드4*/{238, 45},/*키*/{ 283, 3 },/*체중*/{ 286, 3 },
	/*시력좌*/{ 289, 2 },/*시력우*/{ 291, 2 },/*혈액형*/{ 293, 2 },/*군필*/{ 303, 20 },
	/*군별*/{ 305, 1 },/*계급*/{ 306, 1 },/*코드6*/{ 322, 15 },/*코드7*/{ 337, 30 },/*공제flag*/{ 367, 6 } };
	
	
	char* tmp = nullptr;

	for (int i = 0; i < 80941;i=i+373)
	{
		tmp = (char*)calloc(9, sizeof(char));
		
		CString str;
		
		file.Seek(i, CFile::begin);
		file.Read(tmp, 8);
		str = tmp;
		m_dbList.InsertItem(i / 373,str);//사번

		for (int j = 1; j <= sizeof(seek)/sizeof(seek[0]); j++)
		{
			TRACE("넘길 tmp주소 %d 크기 %d\n", tmp,_msize(tmp));
			loadFromTxt(str, file, tmp, i + seek[j-1][0], seek[j-1][1]);
			m_dbList.SetItemText(i/373, j, str);
		}
				
	}
	TRACE("마지막 tmp주소 %d 크기 %d\n", tmp,_msize(tmp));
	tmp = (char*)realloc(tmp, _msize(tmp));
	TRACE("크기 %d 메모리 주소 %d를 해제\n",_msize(tmp), tmp);
	free(tmp);
	file.Close();
}

void Prog_dbmanage::genDbFile()
{
	char *fileName = "Database.db";
	char *query = "CREATE TABLE [PERSON] ( \
		[ID] varchar(8) UNIQUE, \
		[NAME] varchar(8) DEFAULT NULL, \
		[JUMIN] varchar(13) DEFAULT NULL, \
		[ADDRESS] varchar(80) DEFAULT NULL, \
		[PHONE1] varchar(16) DEFAULT NULL, \
		[PHONE2] varchar(16) DEFAULT NULL, \
		[PAY] varchar(2) DEFAULT NULL, \
		[IPSA] varchar(2) DEFAULT NULL, \
		[IPSA_DATE] varchar(8) DEFAULT NULL, \
		[BAL_DATE] varchar(8) DEFAULT NULL, \
		[PROMOTE_DATE] varchar(8) DEFAULT NULL, \
		[ABSENCE_DATE] varchar(8) DEFAULT NULL, \
		[REINSTATEMENT_DATE] varchar(8) DEFAULT NULL, \
		[RETIREMENT_DATE] varchar(8) DEFAULT NULL, \
		[DEPARTMENT] varchar(4) DEFAULT NULL, \
		[POSITION] varchar(3) DEFAULT NULL, \
		[HEIGHT] varchar(3) DEFAULT NULL,[WEIGHT] varchar(3) DEFAULT NULL,\
		[EYE_L] varchar(2) DEFAULT NULL, [EYE_R] varchar(2) DEFAULT NULL, \
		[BLOOD_T] varchar(2) DEFAULT NULL, [FLAG] varchar(6) DEFAULT NULL \
		)";
	

	
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_CreateTable(fileName, query);


	query = "INSERT INTO PERSON (ID, NAME, JUMIN,ADDRESS, PHONE1, PHONE2, \
	PAY , IPSA, IPSA_DATE, BAL_DATE, PROMOTE_DATE ,ABSENCE_DATE ,REINSTATEMENT_DATE ,RETIREMENT_DATE , \
	DEPARTMENT, POSITION, HEIGHT, WEIGHT, EYE_L, EYE_R, BLOOD_T, FLAG) VALUES (";

	int seek[22][2]/*filepointer,charlength*/ = { /*사번*/{0,8},/*이름*/ {8,8},/*주민번호*/{16,13},/*주소*/{29,72},
		/*전화번호*/{101,13},/*전화번호*/{163,12},/*급여구분*/{175,1},
		/*입사경위*/{176,1},/*입사일자*/{181, 8},
		/*발령일자*/{ 189, 8 },/*승진일자*/{ 197, 8 },/*휴직일자*/{ 205, 8 },
		/*복직일자*/{ 213, 8 },/*퇴직일자*/{ 221, 8 },/*부서*/{ 229, 4 },
		/*직급*/{ 235, 3 },/*키*/{ 283, 3 },/*체중*/{ 286, 3 },
		/*시력좌*/{ 289, 2 },/*시력우*/{ 291, 2 },/*혈액형*/{ 293, 2 }, /*공제flag*/{ 367, 6 } };

	pDoc->DB_InsertBulkFromTxt(fileName,query,L"g1101.txt",seek,sizeof(seek)/sizeof(seek[0]), 373);

}

void Prog_dbmanage::genDbFileG2101()
{
	char *fileName = "Database.db";
	/*char *query = "CREATE TABLE [TIMECARD] ( \
		[TIMECARD] varchar(20) DEFAULT NULL, \
		[DETAIL1] varchar(20) DEFAULT NULL, \
		[DETAIL2] varchar(50) DEFAULT NULL \
		)";*/

	char *query = "CREATE TABLE [TIMECARD] ( \
		[DATE] varchar(8) DEFAULT NULL, \
		[ID] varchar(8) DEFAULT NULL, \
		[DAYOFWEEK] varchar(2) DEFAULT NULL, \
		[CODE] varchar(2) DEFAULT NULL, \
		[GETWORKTIME] varchar(6) DEFAULT NULL, \
		[LEAVETIME] varchar(6) DEFAULT NULL, \
		[DAYORNIGHT] varchar(1) DEFAULT NULL, \
		[OVERTIME] varchar(13) DEFAULT NULL,\
		[HOLYDAYWORK] varchar(13) DEFAULT NULL, \
		[OUTTIME] varchar(4) DEFAULT NULL, \
		[REPORTDATE] varchar(8) DEFAULT NULL \
		)";

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_CreateTable(fileName, query);


	query = "INSERT INTO TIMECARD (DATE, ID, DAYOFWEEK, CODE, GETWORKTIME,LEAVETIME,DAYORNIGHT,OVERTIME,HOLYDAYWORK,OUTTIME,REPORTDATE) VALUES (";

	//int seek[3][2]/*filepointer,charlength*/ = { /*TIMECARD*/{0,19},/*DETAIL1*/ {23,17},/*DETAIL2*/{41,49}};
	int seek[11][2]/*filepointer,charlength*/ = { /*DATE*/{0,8},/*ID*/ {8,8},/*DAYOFWEEK*/{16,1},/*CODE*/{17,2},
		/*GETWORKTIME*/{23,8},/*LEAVETIME*/{31,8},/*DAYORNIGHT*/{39,1},/*OVERTIME*/{49,4},/*HOLYDAYWORK*/{57,4},
		/*OUTTIME*/{65,4},/*REPORTDATE*/{69,8}};

	pDoc->DB_InsertBulkFromTxt(fileName, query, L"g2101.txt", seek, sizeof(seek) / sizeof(seek[0]), 96);

}

void Prog_dbmanage::genDbFileCODE1()
{
	char *fileName = "Database.db";
	/*char *query = "CREATE TABLE [TIMECARD] ( \
		[TIMECARD] varchar(20) DEFAULT NULL, \
		[DETAIL1] varchar(20) DEFAULT NULL, \
		[DETAIL2] varchar(50) DEFAULT NULL \
		)";*/

	char *query = "CREATE TABLE [CODE1] ( \
		[CODE1] varchar(20) UNIQUE, \
		[NAME] varchar(30) DEFAULT NULL \
		)";

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_CreateTable(fileName, query);


	query = "INSERT INTO CODE1 (CODE1, NAME) VALUES (";

	//int seek[3][2]/*filepointer,charlength*/ = { /*TIMECARD*/{0,19},/*DETAIL1*/ {23,17},/*DETAIL2*/{41,49}};
	int seek[2][2]/*filepointer,charlength*/ = { /*CODE1*/{6,3},/*NAME*/ {14,26}};
		
	pDoc->DB_InsertBulkFromTxtLine(fileName, query, L"code1.txt", seek, sizeof(seek) / sizeof(seek[0]), 50);

}

void Prog_dbmanage::genDbFileCODE2()
{
	char *fileName = "Database.db";
	/*char *query = "CREATE TABLE [TIMECARD] ( \
		[TIMECARD] varchar(20) DEFAULT NULL, \
		[DETAIL1] varchar(20) DEFAULT NULL, \
		[DETAIL2] varchar(50) DEFAULT NULL \
		)";*/

	char *query = "CREATE TABLE [CODE2] ( \
		[CATEGORY] varchar(20) DEFAULT NULL, \
		[CODE2] varchar(20) DEFAULT NULL, \
		[NAME] varchar(30) DEFAULT NULL, \
		PRIMARY KEY(CATEGORY, CODE2) \
		)";

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_CreateTable(fileName, query);


	query = "INSERT INTO CODE2 (CATEGORY, CODE2, NAME) VALUES (";

	//int seek[3][2]/*filepointer,charlength*/ = { /*TIMECARD*/{0,19},/*DETAIL1*/ {23,17},/*DETAIL2*/{41,49}};
	int seek[3][2]/*filepointer,charlength*/ = { /*CODE2*/{2,3},/*CODE2*/{6,7},/*NAME*/ {14,26} };

	pDoc->DB_InsertBulkFromTxtLine(fileName, query, L"code2.txt", seek, sizeof(seek) / sizeof(seek[0]), 50);

}

void Prog_dbmanage::genDbFileHOLYDAY()
{
	char *fileName = "Database.db";
	
	char *query = "CREATE TABLE [HOLYDAY] ( \
		[DATE] varchar(8) DEFAULT NULL, \
		[ID] varchar(8) DEFAULT NULL, \
		[DAYOFWEEK] varchar(2) DEFAULT NULL, \
		[CODE] varchar(2) DEFAULT NULL, \
		[GETWORKTIME] varchar(6) DEFAULT NULL, \
		[LEAVETIME] varchar(6) DEFAULT NULL, \
		[DAYORNIGHT] varchar(1) DEFAULT NULL, \
		[OVERTIME] varchar(13) DEFAULT NULL,\
		[HOLYDAYWORK] varchar(13) DEFAULT NULL, \
		[OUTTIME] varchar(4) DEFAULT NULL, \
		[REPORTDATE] varchar(8) DEFAULT NULL \
		)";

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_CreateTable(fileName, query);


}



void Prog_dbmanage::OnBnClickedGendb()//디비생성 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int index = m_dbSelect.GetCurSel();
	m_dbSelect.GetLBText(index, str);
	   	
	AfxMessageBox(str);
	
	if (str == _T("PERSON")) {
		genDbFile();
	}
	else if (str == _T("TIMECARD")) {
		genDbFileG2101();
	}
	else if (str == _T("CODE1")) {
		genDbFileCODE1();
	}
	else if (str == _T("CODE2")) {
		genDbFileCODE2();
	}
	else if (str == _T("HOLYDAY")) {
		TRACE("없음\n");
	}
	

	AfxMessageBox(L"디비생성 완료");

}

void Prog_dbmanage::OnClickedDbview()//디비표시 버튼
{
	m_dbList.DeleteAllItems();
	while (m_dbList.DeleteColumn(0));
	UpdateData(TRUE);

	CString str;
	int index = m_dbSelect.GetCurSel();
	m_dbSelect.GetLBText(index, str);
	
	char* stringFrCtrl = StringToChar(str);
	char* file = "Database.db";
	char* query = "SELECT * FROM ";

	int sqLen = strlen(query) + strlen(stringFrCtrl) + 2;
	char* sql = new char[sqLen];
	memset(sql, 0x00, sizeof(char));
	strcpy_s(sql, strlen(query) + 1, query);
	strcat_s(sql, strlen(sql) + strlen(stringFrCtrl) + 1, stringFrCtrl);
	strcat_s(sql, strlen(sql) + 2, ";");
	
	str.Format(L"%s", CString(sql));
	AfxMessageBox(str);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, sql, m_dbList, m_arTxts,Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	

	str.ReleaseBuffer();
	delete[] sql, stringFrCtrl;
	stringFrCtrl = NULL;
	sql = NULL;
	file = NULL;

}


void Prog_dbmanage::genColumns()
{
	CRect rect;
	m_dbList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_dbList.GetClientRect(&rect);
	m_dbList.InsertColumn(0, L"사번", LVCFMT_LEFT, 60);
	m_dbList.InsertColumn(1, L"이름", LVCFMT_RIGHT, 60);
	m_dbList.InsertColumn(2, L"주민번호", LVCFMT_CENTER, 120);
	m_dbList.InsertColumn(3, L"주소", LVCFMT_LEFT, 400);
	m_dbList.InsertColumn(4, L"전화번호1", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(5, L"빈칸", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(6, L"전화번호2", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(7, L"급여구분", LVCFMT_LEFT, 50);
	m_dbList.InsertColumn(8, L"입사경위", LVCFMT_LEFT, 50);
	m_dbList.InsertColumn(9, L"코드", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(10, L"코드2", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(11, L"입사일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(12, L"발령일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(13, L"승진일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(14, L"휴직일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(15, L"복직일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(16, L"퇴직일자", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(17, L"부서", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(18, L"직급", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(19, L"코드4", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(20, L"키(cm)", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(21, L"체중(kg)", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(22, L"시력(좌)", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(23, L"시력(우)", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(24, L"혈액형", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(25, L"군필", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(26, L"군별", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(27, L"계급", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(28, L"코드6", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(29, L"코드7", LVCFMT_LEFT, 100);
	m_dbList.InsertColumn(30, L"공제flag", LVCFMT_LEFT, 100);
}

char* Prog_dbmanage::StringToChar(CString str)
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

void Prog_dbmanage::OnBnClickedTextview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	genDbfromTxt();
}

void Prog_dbmanage::init_dbSelect()
{
	m_dbSelect.AddString(_T("PERSON"));
	m_dbSelect.AddString(_T("TIMECARD"));
	m_dbSelect.AddString(_T("CODE1"));
	m_dbSelect.AddString(_T("CODE2"));
	m_dbSelect.AddString(_T("HOLYDAY"));
}

void Prog_dbmanage::OnSelchangeTableselect()
{
	/*CString str;
	int index = m_dbSelect.GetCurSel();
	m_dbSelect.GetLBText(index, str);
	
	
	char* stringFrCtrl = StringToChar(str);
	char* file = "Database.db";
	char* query = "SELECT * FROM ";

	int sqLen = strlen(query) + strlen(stringFrCtrl) + 2;
	char* sql = new char[sqLen];
	memset(sql, 0x00, sizeof(char));
	strcpy_s(sql, strlen(query)+1, query);
	strcat_s(sql, strlen(sql)+strlen(stringFrCtrl)+1, stringFrCtrl);
	strcat_s(sql, strlen(sql) + 2, ";");



	
	TRACE("셀랙트%s\n", sql);


	str.Format(L"%s", CString(sql));
	AfxMessageBox(str);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	pDoc->DB_GetTable(file, sql, m_dbList);

	str.ReleaseBuffer();
	delete[] sql, stringFrCtrl;
	stringFrCtrl = NULL;
	sql = NULL;
	file = NULL;*/
}

void Prog_dbmanage::loadFromTxt(CString &str,CFile &file, char*& tmp, long filepointer, int charlength)
{
	if (_msize(tmp)-1 != charlength)
	{
		char* old = tmp;
		tmp = (char*)realloc(tmp, sizeof(char) * charlength);
		memset(tmp, 0x00, charlength + 1);
		
	}
	
	file.Seek(filepointer, CFile::begin);
	file.Read(tmp, charlength);
	str = tmp;
	
}

void Prog_dbmanage::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;
	
	CString rLabel;
	int itemCount = m_dbList.GetItemCount();
	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		//TRACE("BeforeSwitch\n");
		//lstrcpy(pItem->pszText, rLabel);
		
		rLabel = m_arTxts.ElementAt(pItem->iItem + pItem->iSubItem*itemCount);

		lstrcpy(pItem->pszText, rLabel);
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