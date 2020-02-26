#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Code_Personpay_List.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Code_Personpay_List, CFormView)

Code_Personpay_List::Code_Personpay_List() :CFormView(Code_Personpay_List::IDD)
,e_code1(_T("")),e_code2(_T("")), e_code1_name(_T("")), e_code2_name(_T(""))
{
}


Code_Personpay_List::~Code_Personpay_List()
{
}

void Code_Personpay_List::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE_1, m_code1List);
	DDX_Control(pDX, IDC_CODE_2, m_code2List);
	DDX_Text(pDX, IDC_CODE1, e_code1);
	DDX_Text(pDX, IDC_CODE2, e_code2);
	DDX_Text(pDX, IDC_CODE1_NAME, e_code1_name);
	DDX_Text(pDX, IDC_CODE2_NAME, e_code2_name);
}


BEGIN_MESSAGE_MAP(Code_Personpay_List, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_CODE_1, GetDispInfo)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_CODE_2, GetDispInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CODE_1, &Code_Personpay_List::OnItemchangedPersonIdName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CODE_2, &Code_Personpay_List::OnItemchangedPersonIdName2)
	ON_BN_CLICKED(IDC_CODE_CANCEL, &Code_Personpay_List::OnClickedBack)
	ON_BN_CLICKED(IDC_CODE_CANCEL2, &Code_Personpay_List::OnClickedBack)
	ON_BN_CLICKED(IDC_CODE_ADD, &Code_Personpay_List::OnClickedNew)
	ON_BN_CLICKED(IDC_CODE_ADD2, &Code_Personpay_List::OnClickedNew2)
	ON_BN_CLICKED(IDC_CODE_EDIT, &Code_Personpay_List::OnClickedEdit)
	ON_BN_CLICKED(IDC_CODE_EDIT2, &Code_Personpay_List::OnClickedEdit2)
	ON_BN_CLICKED(IDC_CODE_DELETE, &Code_Personpay_List::OnClickedDelete)
	ON_BN_CLICKED(IDC_CODE_DELETE2, &Code_Personpay_List::OnClickedDelete2)

END_MESSAGE_MAP()

#ifdef _DEBUG
void Code_Personpay_List::AssertValid() const
{
	CFormView::AssertValid();
}

void Code_Personpay_List::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Code_Personpay_List::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Code_Personpay_List::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Code_Personpay_List::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Code_Personpay_List::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Code_Personpay_List::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	m_code1List.DeleteAllItems();
	m_code2List.DeleteAllItems();
	while (m_code1List.DeleteColumn(0));
	while (m_code2List.DeleteColumn(0));
	UpdateData(TRUE);
	




	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	char* file = "Database.db";
	char* query = "SELECT CODE1, NAME FROM CODE1;";


	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_code1List, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);
	
	query = "SELECT CATEGORY, CODE2, NAME FROM CODE2;";
	pDoc->DB_GetTable(file, query, m_code2List, m_arTxts2, Col);
	
	file = NULL;


	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Code_Personpay_List::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Code_Personpay_List);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Code_Personpay_List::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;
	
	CString rLabel;
	int itemCount = m_code1List.GetItemCount();
	int itemCount2 = m_code2List.GetItemCount();

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		//TRACE("BeforeSwitch\n");
		//lstrcpy(pItem->pszText, rLabel);

		if (IDC_CODE_1 == pNMHDR->idFrom) {

			rLabel = m_arTxts.ElementAt(pItem->iItem + pItem->iSubItem*itemCount);

			lstrcpy(pItem->pszText, rLabel);
		}
		if (IDC_CODE_2 == pNMHDR->idFrom) {

			rLabel = m_arTxts2.ElementAt(pItem->iItem + pItem->iSubItem*itemCount2);

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


void Code_Personpay_List::OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	m_code2List.DeleteAllItems();
	while (m_code2List.DeleteColumn(0));

	e_code1 = m_code1List.GetItemText(p->iItem, p->iSubItem).Trim();
	e_code1_name = m_code1List.GetItemText(p->iItem, p->iSubItem + 1).Trim();
	e_code2 = _T("");
	e_code2_name = _T("");

	if (p->uNewState != 0)
	{
		

		CString str = m_code1List.GetItemText(p->iItem, p->iSubItem);
		
		str.Trim();
		char* tmp = pDoc->StringToChar(str);
		
		char* file = "Database.db";
		char* query = "SELECT * FROM CODE2 WHERE CATEGORY = '";
		
		

		int strLen = strlen(query);
		int tmpLen = strlen(tmp);
		
		char* sql = new char[strLen + tmpLen + 2];
		
		strcpy_s(sql, strLen + 1, query);
		strcpy_s(sql + strLen, tmpLen + 1, tmp);
		strcpy_s(sql+ strlen(sql), 2 , "'");
				

		LVCOLUMN Col;
		pDoc->DB_GetTable(file, sql, m_code2List, m_arTxts2, Col);
		file = NULL;
	
		

		
				
		delete[] sql;
		
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void Code_Personpay_List::OnItemchangedPersonIdName2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	
	TRACE("selected\n");
	e_code2 = m_code2List.GetItemText(p->iItem, p->iSubItem+1).Trim();
	e_code2_name = m_code2List.GetItemText(p->iItem, p->iSubItem + 2).Trim();
	
	
	
	if (p->uNewState != 0)
	{
		
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void Code_Personpay_List::OnClickedBack()
{
	UpdateData(FALSE);
}

void Code_Personpay_List::OnClickedNew()
{
	int index = m_code1List.GetItemCount();
	
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char *fileName = "Database.db";
	char *query = "INSERT INTO CODE1 (CODE1, NAME) VALUES (";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];

	char* s = pDoc->DB_ConCat("%s '%s','%s');",
		query, pDoc->StringToChar(e_code1), pDoc->StringToChar(e_code1_name));
		
	pDoc->DB_SendQuery(fileName, s);



	m_code1List.DeleteAllItems();
	while (m_code1List.DeleteColumn(0));
	query = "SELECT CODE1, NAME FROM CODE1;";
	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, query, m_code1List, m_arTxts, Col);
	UpdateData(FALSE);


	m_code1List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code1List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code1List.EnsureVisible(index, FALSE);
	m_code1List.SetFocus();

}

void Code_Personpay_List::OnClickedNew2()
{
	int index = m_code2List.GetItemCount();
	
	UpdateData(TRUE);

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char *fileName = "Database.db";
	char *query = "INSERT INTO CODE2 (CATEGORY, CODE2, NAME) VALUES (";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];

	char* s = pDoc->DB_ConCat("%s '%s','%s','%s');",
		query, pDoc->StringToChar(e_code1), pDoc->StringToChar(e_code2), pDoc->StringToChar(e_code2_name));

	pDoc->DB_SendQuery(fileName, s);



	m_code2List.DeleteAllItems();
	while (m_code2List.DeleteColumn(0));
	query = "SELECT CATEGORY, CODE2, NAME FROM CODE2 WHERE CATEGORY = ";
	s = pDoc->DB_ConCat("%s '%s';",
		query, pDoc->StringToChar(e_code1));


	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, s, m_code2List, m_arTxts2, Col);
	UpdateData(FALSE);


	m_code2List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code2List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code2List.EnsureVisible(index, FALSE);
	m_code2List.SetFocus();
}

void Code_Personpay_List::OnClickedEdit()
{
	int index = m_code1List.GetItemCount();
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char* code1 = pDoc->StringToChar(e_code1);
	UpdateData(TRUE);

	
	char *fileName = "Database.db";
	char *query = "UPDATE CODE1 SET ";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];
	
	char* s = pDoc->DB_ConCat("%s CODE1='%s',NAME='%s' WHERE CODE1='%s';",
		query, pDoc->StringToChar(e_code1), pDoc->StringToChar(e_code1_name), code1);

	pDoc->DB_SendQuery(fileName, s);



	m_code1List.DeleteAllItems();
	while (m_code1List.DeleteColumn(0));
	query = "SELECT CODE1, NAME FROM CODE1;";
	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, query, m_code1List, m_arTxts, Col);
	UpdateData(FALSE);


	m_code1List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code1List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code1List.EnsureVisible(index, FALSE);
	m_code1List.SetFocus();
}
void Code_Personpay_List::OnClickedEdit2()
{
	int index = m_code2List.GetItemCount();
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char* code2 = pDoc->StringToChar(e_code2);
	UpdateData(TRUE);

	
	char *fileName = "Database.db";
	char *query = "UPDATE CODE2 SET ";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];
	
	char* s = pDoc->DB_ConCat("%s CODE2='%s',NAME='%s' WHERE CODE2='%s';",
		query, pDoc->StringToChar(e_code2), pDoc->StringToChar(e_code2_name), code2);

	pDoc->DB_SendQuery(fileName, s);



	m_code2List.DeleteAllItems();
	while (m_code2List.DeleteColumn(0));
	query = "SELECT CATEGORY, CODE2, NAME FROM CODE2 WHERE CATEGORY = ";
	s = pDoc->DB_ConCat("%s '%s';",
		query, pDoc->StringToChar(e_code1));


	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, s, m_code2List, m_arTxts2, Col);
	UpdateData(FALSE);


	m_code2List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code2List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code2List.EnsureVisible(index, FALSE);
	m_code2List.SetFocus();
}
void Code_Personpay_List::OnClickedDelete()
{
	int index = m_code1List.GetItemCount();
	if (m_code2List.GetItemCount() > 0) 
	{
		AfxMessageBox(_T("세부항목이 있는 코드는 삭제할 수 없습니다."));
		return;
	}

	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	
	UpdateData(TRUE);


	char *fileName = "Database.db";
	char *query = "DELETE FROM CODE1 ";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];

	char* s = pDoc->DB_ConCat("%s WHERE CODE1='%s';",
		query, pDoc->StringToChar(e_code1));

	pDoc->DB_SendQuery(fileName, s);



	m_code1List.DeleteAllItems();
	while (m_code1List.DeleteColumn(0));
	query = "SELECT CODE1, NAME FROM CODE1;";
	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, query, m_code1List, m_arTxts, Col);
	UpdateData(FALSE);


	m_code1List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code1List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code1List.EnsureVisible(index, FALSE);
	m_code1List.SetFocus();
}
void Code_Personpay_List::OnClickedDelete2()
{
	int index = m_code2List.GetItemCount();
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	
	UpdateData(TRUE);


	char *fileName = "Database.db";
	char *query = "DELETE FROM CODE2 ";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];

	char* s = pDoc->DB_ConCat("%s WHERE CODE2='%s';",
		query, pDoc->StringToChar(e_code2));

	pDoc->DB_SendQuery(fileName, s);



	m_code2List.DeleteAllItems();
	while (m_code2List.DeleteColumn(0));
	query = "SELECT CATEGORY, CODE2, NAME FROM CODE2 WHERE CATEGORY = ";
	s = pDoc->DB_ConCat("%s '%s';",
		query, pDoc->StringToChar(e_code1));


	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, s, m_code2List, m_arTxts2, Col);
	UpdateData(FALSE);


	m_code2List.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_code2List.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_code2List.EnsureVisible(index, FALSE);
	m_code2List.SetFocus();
}