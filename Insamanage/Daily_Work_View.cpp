#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Daily_Work_View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Daily_Work_View, CFormView)

Daily_Work_View::Daily_Work_View() :CFormView(Daily_Work_View::IDD)
{
}


Daily_Work_View::~Daily_Work_View()
{
}

void Daily_Work_View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DAILY_WORK_LIST, m_ctrDaily);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrDateTime);
}


BEGIN_MESSAGE_MAP(Daily_Work_View, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DAILY_WORK_LIST, GetDispInfo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Daily_Work_View::OnDtnDatetimechangeDatetimepicker1)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, RadioCtrl)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Daily_Work_View::AssertValid() const
{
	CFormView::AssertValid();
}

void Daily_Work_View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Daily_Work_View::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Daily_Work_View::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Daily_Work_View::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Daily_Work_View::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Daily_Work_View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_ctrDaily.DeleteAllItems();
	while (m_ctrDaily.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	char* query = "SELECT ID, NAME FROM PERSON;";

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrDaily, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;


	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Daily_Work_View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Daily_Work_View);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Daily_Work_View::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_ctrDaily.GetItemCount();


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

void Daily_Work_View::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TRACE("날짜가 변경됨 %02d::%02d::%04d  %d\n", pDTChange->st.wDay, pDTChange->st.wMonth, pDTChange->st.wYear, pDTChange->st.wDayOfWeek);

	m_ctrDaily.DeleteAllItems();
	while (m_ctrDaily.DeleteColumn(0));
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
	pDoc->DB_GetTable(file, query, m_ctrDaily, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;

	*pResult = 0;



}

void Daily_Work_View::RadioCtrl(UINT id)
{
	

	m_ctrDaily.DeleteAllItems();
	while (m_ctrDaily.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();


	COleDateTime time;
	m_ctrDateTime.GetTime(time);

	char* date = new char[10];
	sprintf_s(date, _msize(date), "%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());
	char* file = "Database.db";
	char* query = new char[250];


	switch (id)
	{
	case IDC_RADIO1:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s", date);
		
		break;
	case IDC_RADIO2:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and pay = 1", date);
		
		break;
	case IDC_RADIO3:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and pay = 6", date);
		
		break;

	}



	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrDaily, m_arTxts, Col);

	file = NULL;



}