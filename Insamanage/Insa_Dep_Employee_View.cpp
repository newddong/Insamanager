#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Insa_Dep_Employee_View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Insa_Dep_Employee_View, CFormView)

Insa_Dep_Employee_View::Insa_Dep_Employee_View() :CFormView(Insa_Dep_Employee_View::IDD)
{
}


Insa_Dep_Employee_View::~Insa_Dep_Employee_View()
{
}

void Insa_Dep_Employee_View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEPARTMENT, m_ctrlDep);
	DDX_Control(pDX, IDC_DEPEMPLOYEE, m_ctrEmployee);
}


BEGIN_MESSAGE_MAP(Insa_Dep_Employee_View, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DEPEMPLOYEE, GetDispInfo)
	ON_CBN_SELCHANGE(IDC_DEPARTMENT, &Insa_Dep_Employee_View::OnSelchangeDepartment)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Insa_Dep_Employee_View::AssertValid() const
{
	CFormView::AssertValid();
}

void Insa_Dep_Employee_View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Insa_Dep_Employee_View::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Insa_Dep_Employee_View::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Insa_Dep_Employee_View::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Insa_Dep_Employee_View::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Insa_Dep_Employee_View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char* file = "Database.db";
	char* query = "select department, ifnull(dep,'') as dep from person left outer join (select code2 as cod, name as dep from code2 where category = 'P40') on department = trim(cod) group by department";
	
	int rows, columns;
	char** result = pDoc->DB_GetTable(file, query, rows, columns);
	TRACE("%s\n", query);
	TRACE("rows %d, columns %d\n", rows, columns);
	
	char* tmp = new char[50];
	for (int i = 1; i <= rows; i++) {
		

		sprintf_s(tmp, _msize(tmp), "%s %s", result[i*columns], result[i*columns + 1]);
		m_ctrlDep.AddString(CString(tmp));
			
		
	}
	delete[] tmp;

	query = "select id as 사번, name as 이름, substr(jumin,1,6)||'-'||substr(jumin,-7,7) as 주민번호,address as 주소, substr(ipsa_date,1,4)||'년'||substr(ipsa_date,5,2)||'월'||substr(ipsa_date,7,2)||'일' as 입사일자  from person";
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_ctrEmployee, m_arTxts, Col);



	/*for (int i = 0; i <= rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			free(result[i*columns + j]);
		}
	}
	delete[] query;*/
	free(result);
	file = NULL;
	
	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Insa_Dep_Employee_View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Insa_Dep_Employee_View);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Insa_Dep_Employee_View::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	CString rLabel;
	int itemCount = m_ctrEmployee.GetItemCount();


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

void Insa_Dep_Employee_View::OnSelchangeDepartment()
{
	m_ctrEmployee.DeleteAllItems();
	while (m_ctrEmployee.DeleteColumn(0));
	UpdateData(TRUE);
	
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	int cur = m_ctrlDep.GetCurSel();
	CString tmp;
	
	m_ctrlDep.GetLBText(cur, tmp);
	
	char* tmpchar = pDoc->StringToChar(tmp.Left(4));

	char* file = "Database.db";
	char* query = "select id as 사번, name as 이름, substr(jumin,1,6)||'-'||substr(jumin,-7,7) as 주민번호, \
address as 주소, substr(ipsa_date,1,4)||'년'||substr(ipsa_date,5,2)||'월'||substr(ipsa_date,7,2)||'일' as 입사일자 from person \
where department =";
	
	char* buf = new char[300];
	sprintf_s(buf,_msize(buf), "%s '%s';", query, tmpchar);
	
	TRACE("%s\n", buf);
	int rows, columns;
	
	
	//char** result = pDoc->DB_GetTable(file, query, rows, columns);
	

	LVCOLUMN Col;
	pDoc->DB_GetTable(file, buf, m_ctrEmployee, m_arTxts, Col);

	delete[] buf;
	//free(result);
	file = NULL;


}
