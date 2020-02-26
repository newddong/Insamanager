#include "stdafx.h"


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

	query = "select id as ���, name as �̸�, substr(jumin,1,6)||'-'||substr(jumin,-7,7) as �ֹι�ȣ,address as �ּ�, substr(ipsa_date,1,4)||'��'||substr(ipsa_date,5,2)||'��'||substr(ipsa_date,7,2)||'��' as �Ի�����  from person";
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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
		//	wsprintf(pItem->pszText, L"�ι�°%s", rLabel);
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
	
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	int cur = m_ctrlDep.GetCurSel();
	CString tmp;
	
	m_ctrlDep.GetLBText(cur, tmp);
	
	char* tmpchar = pDoc->StringToChar(tmp.Left(4));

	char* file = "Database.db";
	char* query = "select id as ���, name as �̸�, substr(jumin,1,6)||'-'||substr(jumin,-7,7) as �ֹι�ȣ, \
address as �ּ�, substr(ipsa_date,1,4)||'��'||substr(ipsa_date,5,2)||'��'||substr(ipsa_date,7,2)||'��' as �Ի����� from person \
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
