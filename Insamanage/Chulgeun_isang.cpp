#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Chulgeun_isang.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Chulgeun_isang, CFormView)

Chulgeun_isang::Chulgeun_isang():CFormView(Chulgeun_isang::IDD)
, radio_pay(0),radio_sex(0)
{
}


Chulgeun_isang::~Chulgeun_isang()
{
}

void Chulgeun_isang::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHULGEUN_ISANG, m_ctrChul);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrDateTime);
	//DDX_Radio(pDX, IDC_CHUL_ISANG_R1, (int&)radio_pay);
	//DDX_Radio(pDX, IDC_CHUL_ISANG_R4, (int&)radio_sex);
}


BEGIN_MESSAGE_MAP(Chulgeun_isang, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_CHULGEUN_ISANG, GetDispInfo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &Chulgeun_isang::OnDtnDatetimechangeDatetimepicker1)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHUL_ISANG_R1, IDC_CHUL_ISANG_R3, RadioCtrl)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHUL_ISANG_R4, IDC_CHUL_ISANG_R6, RadioCtrl2)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Chulgeun_isang::AssertValid() const
{
	CFormView::AssertValid();
}

void Chulgeun_isang::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Chulgeun_isang::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Chulgeun_isang::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:
	
	
	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);
	
}


BOOL Chulgeun_isang::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Chulgeun_isang::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);
	
	pDC->DPtoLP(&rectClient);
		
	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Chulgeun_isang::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char* file = "Database.db";
	COleDateTime time;
	m_ctrDateTime.GetTime(time);

	char* query = new char[350];
	char* date = new char[10];
	
	sprintf_s(date, _msize(date), "%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());
	sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay from person left outer join timecard using (ID) where date = %s",date );

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrChul, m_arTxts, Col);



	/*for (int i = 0; i <= rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			free(result[i*columns + j]);
		}
	}
	delete[] query;*/
	delete[] query;
	file = NULL;
	

	//CSize sizeTotal;
	// TODO: calculate the total size of this view
	
	SetScrollSizes(MM_TEXT, CSize(1200,800));
			
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Chulgeun_isang::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_CHULGEUN_ISANG);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);
	
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Chulgeun_isang::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_ctrChul.GetItemCount();


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


void Chulgeun_isang::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TRACE("날짜가 변경됨 %02d::%02d::%04d  %d\n", pDTChange->st.wDay, pDTChange->st.wMonth, pDTChange->st.wYear, pDTChange->st.wDayOfWeek);

	m_ctrChul.DeleteAllItems();
	while (m_ctrChul.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	//char* query = "SELECT ID, NAME FROM PERSON;";
	char* query = new char[250];
	char* selectday = new char[10];
	sprintf_s(selectday, _msize(selectday), "%04d%02d%02d", pDTChange->st.wYear, pDTChange->st.wMonth, pDTChange->st.wDay);
	sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay from person left outer join timecard using (ID)where date = %s", selectday);
	
	TRACE("query %s \n", query);
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrChul, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);

	file = NULL;

	*pResult = 0;



}

void Chulgeun_isang::RadioCtrl(UINT id)
{
	TRACE("radio pay : %d\n", radio_pay);
	
	m_ctrChul.DeleteAllItems();
	while (m_ctrChul.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();


	COleDateTime time;
	m_ctrDateTime.GetTime(time);
		
	char* date = new char[10];
	sprintf_s(date, _msize(date), "%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());
	char* file = "Database.db";
	char* query = new char[250];

	char* sex = new char[30];
	switch (radio_sex)
	{
	case 0:
		sprintf_s(sex, _msize(sex), "");
		break;
	default:
		sprintf_s(sex, _msize(sex), "and substr(jumin,7,1)= '%d'", radio_sex);
		break;
	}


	switch (id)
	{
	case IDC_CHUL_ISANG_R1:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s %s", date, sex);
		radio_pay = 0;
		break;
	case IDC_CHUL_ISANG_R2:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and pay = 1 %s", date,sex);
		radio_pay = 1;
		break;
	case IDC_CHUL_ISANG_R3:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and pay = 6 %s", date,sex);
		radio_pay = 6;
		break;

	}

	
		
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrChul, m_arTxts, Col);
	
	file = NULL;


}


void Chulgeun_isang::RadioCtrl2(UINT id)
{
	TRACE("radio sex : %d\n", radio_sex);
	m_ctrChul.DeleteAllItems();
	while (m_ctrChul.DeleteColumn(0));
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();


	COleDateTime time;
	m_ctrDateTime.GetTime(time);

	char* date = new char[10];
	sprintf_s(date, _msize(date), "%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());
	char* file = "Database.db";
	char* query = new char[250];

	char* pay = new char[30];
	switch (radio_pay)
	{
	case 0:
		sprintf_s(pay, _msize(pay), "");
		break;
	default:
		sprintf_s(pay, _msize(pay), "and pay = '%d'", radio_pay);
		break;
	}


	switch (id)
	{
	case IDC_CHUL_ISANG_R4:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s %s", date,pay);
		radio_sex = 0;
		break;
	case IDC_CHUL_ISANG_R5:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and cast(substr(jumin,7,1) as integer) %% 2 == 1 %s", date,pay);
		radio_sex = 1;
		break;
	case IDC_CHUL_ISANG_R6:
		sprintf_s(query, _msize(query), "select id as 사번, name as 이름, pay,jumin from person left outer join timecard using (ID)where date = %s and cast(substr(jumin,7,1) as integer) %% 2 == 0 %s", date,pay);
		radio_sex = 2;
		break;

	}



	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrChul, m_arTxts, Col);

	file = NULL;
}
