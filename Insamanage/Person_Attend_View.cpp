
#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Person_Attend_View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Person_Attend_View, CFormView)

Person_Attend_View::Person_Attend_View() :CFormView(Person_Attend_View::IDD),
e_Id(_T("")), e_Name(_T("")), e_Department(_T("")), e_Position(_T(""))
{
}


Person_Attend_View::~Person_Attend_View()
{
}

void Person_Attend_View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_ID_NAME, m_personList);
	DDX_Control(pDX, IDC_LIST1, m_personAttList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrDateTime);
	DDX_Text(pDX,IDC_PERSON_ID,e_Id);
	DDX_Text(pDX,IDC_PERSON_NAME,e_Name);
	DDX_Text(pDX,IDC_PERSON_DEPARTMENT,e_Department);
	DDX_Text(pDX,IDC_PERSON_POSITION,e_Position);

}


BEGIN_MESSAGE_MAP(Person_Attend_View, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Person_Attend_View::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PERSON_ID_NAME, &Person_Attend_View::OnItemchangedPersonIdName)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_PERSON_ID_NAME, GetDispInfo)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, GetDispInfo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Person_Attend_View::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Person_Attend_View::AssertValid() const
{
	CFormView::AssertValid();
}

void Person_Attend_View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Person_Attend_View::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Person_Attend_View::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Person_Attend_View::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Person_Attend_View::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Person_Attend_View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_ctrDateTime.SetFormat(_T("yyyy-MM"));
	COleDateTime time;
	m_ctrDateTime.GetTime(time);
	m_personList.DeleteAllItems();
	m_personAttList.DeleteAllItems();
	while (m_personList.DeleteColumn(0));
	while (m_personAttList.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	char* query = "SELECT ID as 사번, NAME as 성명 FROM PERSON;";

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_personList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	query = "";
	pDoc->DB_GetTable(file, query, m_personAttList, m_arTxts2, Col);

	file = NULL;


	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	
	

}

void Person_Attend_View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Person_Attend_View);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Person_Attend_View::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_personList.GetItemCount();
	int itemCount2 = m_personAttList.GetItemCount();

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		
		if (IDC_PERSON_ID_NAME == pNMHDR->idFrom) {

			
			rLabel = m_arTxts.ElementAt(pItem->iItem + pItem->iSubItem*itemCount);
			lstrcpy(pItem->pszText, rLabel);


		}
		if (IDC_LIST1 == pNMHDR->idFrom) {

			rLabel = m_arTxts2.ElementAt(pItem->iItem + pItem->iSubItem * itemCount2);

			lstrcpy(pItem->pszText, rLabel);
		}

	}


	*pResult = 0;
}

void Person_Attend_View::OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	COleDateTime time;
	m_personAttList.DeleteAllItems();
	while (m_personAttList.DeleteColumn(0));
	UpdateData(TRUE);

	if (p->uNewState != 0)
	{
		CString str = m_personList.GetItemText(p->iItem, p->iSubItem);
		m_nIndofList = p->iItem;
		char* tmp = pDoc->StringToChar(str);
		char* file = "Database.db";
		

		m_ctrDateTime.GetTime(time);

		char* query = new char[250];
		
		sprintf_s(query, 250, "SELECT ID as 사번, NAME as 성명, DATE as 일자 FROM PERSON JOIN TIMECARD USING (ID) WHERE ID = %s and DATE >= %04d%02d00 and DATE < %04d%02d00;", tmp, time.GetYear(), time.GetMonth(), time.GetYear(), time.GetMonth()+1);
		TRACE("sizeof query : %d, query : %s\n", _msize(query), query);
		
		
		LVCOLUMN Col;
		pDoc->DB_GetTable(file, query, m_personAttList, m_arTxts2, Col);

		sprintf_s(query, 250, "SELECT * FROM PERSON WHERE ID = %s;", tmp);
		int rows, columns;
		char** result = pDoc->DB_GetTable(file, query, rows, columns);
		TRACE("Rows %d, col %d\n", rows, columns);

		if (rows >= 1) {
			TRACE("%s %s %s\n", result[columns], result[columns + 1], result[columns + 2]);
			e_Id = CString(result[columns]);
			e_Name = CString(result[columns + 1]);
			e_Department = CString(result[14 + columns]);
			e_Position = CString(result[15 + columns]);
			
		}
		else {
			e_Id = _T("");
			e_Name = _T("");
			e_Department = _T("");
			e_Position = _T("");
			
		}


		UpdateData(FALSE);

		for (int i = 0; i <= rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				free(result[i*columns + j]);
			}
		}
		
		free(result);
		delete[] query;
		
	}

	*pResult = 0;
}

void Person_Attend_View::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TRACE("날짜가 변경됨 %02d::%02d::%04d  %d\n", pDTChange->st.wDay, pDTChange->st.wMonth, pDTChange->st.wYear, pDTChange->st.wDayOfWeek);

	m_personList.DeleteAllItems();
	while (m_personList.DeleteColumn(0));
	m_personAttList.DeleteAllItems();
	while (m_personAttList.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	//char* query = "SELECT ID, NAME FROM PERSON;";
	char* query = new char[250];
	char* selectday = new char[10];
	sprintf_s(selectday, _msize(selectday), "%04d%02d00", pDTChange->st.wYear, pDTChange->st.wMonth);
	sprintf_s(query, _msize(query), "SELECT ID as 사번, NAME as 성명, retirement_date FROM PERSON WHERE (retirement_date > %s OR retirement_date = '00000000') AND ID <= %s", selectday, selectday);

	TRACE("query %s \n", query);
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_personList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;

	*pResult = 0;



}