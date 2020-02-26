#include "stdafx.h"

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Assign_Daily_work.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Assign_Daily_work, CFormView)

Assign_Daily_work::Assign_Daily_work() :CFormView(Assign_Daily_work::IDD)
,e_Id(_T("")), e_Name(_T("")), e_Department(_T("")), e_Position(_T("")), e_Janup(_T("")), e_Tjanup(_T("")), e_Jigak(_T("")),
e_Guencode(_T("")), e_Chuldate(_T("")), e_Backhomedate(_T("")), e_Outtime(_T("")), e_Editdate(_T(""))
{
}


Assign_Daily_work::~Assign_Daily_work()
{
}

void Assign_Daily_work::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_ID_NAME, m_personList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrDateTime);
	DDX_Text(pDX, IDC_PERSON_ID, e_Id);
	DDX_Text(pDX, IDC_PERSON_NAME, e_Name);
	DDX_Text(pDX, IDC_PERSON_DEPARTMENT, e_Department);
	DDX_Text(pDX, IDC_PERSON_POSITION, e_Position);
	DDX_Text(pDX, IDC_JANUP, e_Janup);
	DDX_Text(pDX, IDC_TJANUP, e_Tjanup);
	DDX_Text(pDX, IDC_JIGAK, e_Jigak);
	DDX_Text(pDX, IDC_GUENCODE, e_Guencode);
	DDX_Text(pDX, IDC_CHULDATE, e_Chuldate);
	DDX_Text(pDX, IDC_BACKHOMEDATE, e_Backhomedate);
	DDX_Text(pDX, IDC_OUTTIME, e_Outtime);
	DDX_Text(pDX, IDC_EDITDATE, e_Editdate);

}


BEGIN_MESSAGE_MAP(Assign_Daily_work, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_PERSON_ID_NAME, GetDispInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PERSON_ID_NAME, &Assign_Daily_work::OnItemchangedPersonIdName)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Assign_Daily_work::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Assign_Daily_work::AssertValid() const
{
	CFormView::AssertValid();
}

void Assign_Daily_work::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Assign_Daily_work::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Assign_Daily_work::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Assign_Daily_work::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Assign_Daily_work::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Assign_Daily_work::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_personList.DeleteAllItems();
	while (m_personList.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	char* query = "SELECT ID, NAME FROM PERSON;";

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_personList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;


	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Assign_Daily_work::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);

	//CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_CHULGEUN_ISANG);
	//if (lst == NULL) {
		//AfxMessageBox(L"d");
	//	return;
	//}

	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Assign_Daily_work::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_personList.GetItemCount();
	

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

void Assign_Daily_work::OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	COleDateTime time;

	if (p->uNewState != 0)
	{
		CString str = m_personList.GetItemText(p->iItem, p->iSubItem);
		m_nIndofList = p->iItem;
		char* tmp = pDoc->StringToChar(str);
		char* file = "Database.db";
		//char* query = "SELECT * FROM PERSON WHERE ID = ";
		
		m_ctrDateTime.GetTime(time);
		
		char* query = new char[250];
		//sprintf_s(query, 250, "SELECT * FROM TIMECARD WHERE ID = %s AND DATE = %04d%02d%02d;", tmp,time.GetYear(),time.GetMonth(),time.GetDay());
		sprintf_s(query, 250, "SELECT * FROM PERSON JOIN TIMECARD USING (ID) WHERE ID = %s and DATE = %04d%02d%02d;", tmp, time.GetYear(), time.GetMonth(), time.GetDay());
		TRACE("sizeof query : %d, query : %s\n",_msize(query), query);
		//int strLen = strlen(query);
		//int tmpLen = strlen(tmp);

		//char* sql = new char[strLen + tmpLen + 1];
		//strcpy_s(sql, strLen + 1, query);
		//strcpy_s(sql + strLen, tmpLen + 1, tmp);

		
		int rows, columns;
		char** result = pDoc->DB_GetTable(file, query, rows, columns);
		TRACE("Rows %d, col %d\n", rows, columns);
		
		if (rows >= 1) {
			TRACE("%s %s %s\n", result[columns], result[columns+1], result[columns+2]);
			e_Id = CString(result[columns]);
			e_Name = CString(result[columns+1]);
			e_Department = CString(result[14 + columns]);
			e_Position = CString(result[15 + columns]);
			e_Janup= CString(result[columns+28]);
			e_Tjanup= CString(result[columns+29]);
			e_Jigak= CString(result[columns+30]);
			e_Guencode= CString(result[columns+24]);
			e_Chuldate= CString(result[columns+25]);
			e_Backhomedate= CString(result[columns+26]);
			e_Outtime= CString(result[columns+30]);
			e_Editdate = CString(result[columns + 31]);


		}
		else {
			e_Id = _T("");
			e_Name = _T("");
			e_Department = _T("");
			e_Position = _T("");
			e_Janup = _T("");
			e_Tjanup = _T("");
			e_Jigak = _T("");
			e_Guencode = _T("");
			e_Chuldate = _T("");
			e_Backhomedate = _T("");
			e_Outtime = _T("");
			e_Editdate = _T("");
		}


		UpdateData(FALSE);

		for (int i = 0; i <= rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				free(result[i*columns + j]);
			}
		}
		delete[] query;
		free(result);
	}

	*pResult = 0;
}

void Assign_Daily_work::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TRACE("날짜가 변경됨 %02d::%02d::%04d  %d\n",pDTChange->st.wDay, pDTChange->st.wMonth, pDTChange->st.wYear,pDTChange->st.wDayOfWeek);
	
	m_personList.DeleteAllItems();
	while (m_personList.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	//char* query = "SELECT ID, NAME FROM PERSON;";
	char* query = new char[250];
	char* selectday = new char[10];
	sprintf_s(selectday, _msize(selectday), "%04d%02d%02d", pDTChange->st.wYear, pDTChange->st.wMonth, pDTChange->st.wDay);
	sprintf_s(query, _msize(query), "SELECT ID as 사번, NAME as 성명, retirement_date FROM PERSON WHERE (retirement_date > %s OR retirement_date = '00000000') AND ID <= %s", selectday,selectday);

	TRACE("query %s \n", query);
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_personList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;

	*pResult = 0;



}
