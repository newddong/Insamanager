#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Personal_Day_Assign.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Personal_Day_Assign, CFormView)

Personal_Day_Assign::Personal_Day_Assign() :CFormView(Personal_Day_Assign::IDD)
{
}


Personal_Day_Assign::~Personal_Day_Assign()
{
}

void Personal_Day_Assign::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_dayList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrDateTime);
	DDX_Control(pDX, IDC_DATE_YEAR, m_ctrDateTimeYr);
}


BEGIN_MESSAGE_MAP(Personal_Day_Assign, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, GetDispInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Personal_Day_Assign::OnItemchangedPersonIdName)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Personal_Day_Assign::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_YEAR, &Personal_Day_Assign::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Personal_Day_Assign::AssertValid() const
{
	CFormView::AssertValid();
}

void Personal_Day_Assign::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Personal_Day_Assign::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Personal_Day_Assign::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Personal_Day_Assign::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Personal_Day_Assign::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Personal_Day_Assign::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_dayList.DeleteAllItems();
	while (m_dayList.DeleteColumn(0));
	m_ctrDateTimeYr.SetFormat(_T("yyyy년도"));
	m_ctrDateTime.SetFormat(_T("MM월 dd일 dddd"));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	char* query = "SELECT ID, NAME FROM PERSON;";

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_dayList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;


	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Personal_Day_Assign::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Personal_Day_Assign);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Personal_Day_Assign::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_dayList.GetItemCount();


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

void Personal_Day_Assign::OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	COleDateTime time;

	if (p->uNewState != 0)
	{
		CString str = m_dayList.GetItemText(p->iItem, p->iSubItem);
		m_nIndofList = p->iItem;
		char* tmp = pDoc->StringToChar(str);
		char* file = "Database.db";
		//char* query = "SELECT * FROM PERSON WHERE ID = ";

		m_ctrDateTime.GetTime(time);

		char* query = new char[250];
		//sprintf_s(query, 250, "SELECT * FROM TIMECARD WHERE ID = %s AND DATE = %04d%02d%02d;", tmp,time.GetYear(),time.GetMonth(),time.GetDay());
		sprintf_s(query, 250, "SELECT * FROM PERSON JOIN TIMECARD USING (ID) WHERE ID = %s and DATE = %04d%02d%02d;", tmp, time.GetYear(), time.GetMonth(), time.GetDay());
		TRACE("sizeof query : %d, query : %s\n", _msize(query), query);
		//int strLen = strlen(query);
		//int tmpLen = strlen(tmp);

		//char* sql = new char[strLen + tmpLen + 1];
		//strcpy_s(sql, strLen + 1, query);
		//strcpy_s(sql + strLen, tmpLen + 1, tmp);


		int rows, columns;
		char** result = pDoc->DB_GetTable(file, query, rows, columns);
		TRACE("Rows %d, col %d\n", rows, columns);

		


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

void Personal_Day_Assign::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TRACE("%d 날짜가 변경됨 %02d::%02d::%04d  %d\n",pDTChange->nmhdr.idFrom, pDTChange->st.wDay, pDTChange->st.wMonth, pDTChange->st.wYear, pDTChange->st.wDayOfWeek);
	COleDateTime tmpTime;
	if (pDTChange->nmhdr.idFrom == IDC_DATE_YEAR) {
		m_ctrDateTime.GetTime(tmpTime);
		tmpTime.SetDate(pDTChange->st.wYear, tmpTime.GetMonth(), tmpTime.GetDay());
		m_ctrDateTime.SetTime(tmpTime);
		
		TRACE("작동함\n");
	}



	m_dayList.DeleteAllItems();
	while (m_dayList.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	//char* query = "SELECT ID, NAME FROM PERSON;";
	char* query = new char[250];
	char* selectday = new char[10];
	sprintf_s(selectday, _msize(selectday), "%04d%02d%02d", pDTChange->st.wYear, pDTChange->st.wMonth, pDTChange->st.wDay);
	sprintf_s(query, _msize(query), "SELECT ID as 사번, NAME as 성명, retirement_date FROM PERSON WHERE (retirement_date > %s OR retirement_date = '00000000') AND ID <= %s", selectday, selectday);

	TRACE("query %s \n", query);
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_dayList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;

	*pResult = 0;



}