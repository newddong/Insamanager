#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Insa_Person_Info_Assign.h"
#include "CInsaListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Insa_Person_Info_Assign, CFormView)

Insa_Person_Info_Assign::Insa_Person_Info_Assign() :CFormView(Insa_Person_Info_Assign::IDD)
, e_Id(_T(""))
, e_Name(_T(""))
, e_Jumin(_T(""))
, e_Address(_T(""))
, e_Phone1(_T(""))
, e_Phone2(_T(""))
, e_Department(_T(""))
, e_Position(_T(""))
, e_Pay(_T(""))
, e_Ipsa(_T(""))
, e_Flag(_T(""))
, e_IpsaDate(_T(""))
, e_BalDate(_T(""))
, e_PromoteDate(_T(""))
, e_AbsenceDate(_T(""))
, e_ReinstatementDate(_T(""))
, e_RetirementDate(_T(""))
, e_Height(_T(""))
, e_Weight(_T(""))
, e_EyeL(_T(""))
, e_EyeR(_T(""))
, e_Blood(_T(""))
{
}


Insa_Person_Info_Assign::~Insa_Person_Info_Assign()
{
}

void Insa_Person_Info_Assign::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_ID_NAME, m_dbList);
	DDX_Text(pDX, IDC_PERSON_ID, e_Id);
	DDX_Text(pDX, IDC_PERSON_NAME, e_Name);
	DDX_Text(pDX, IDC_PERSON_JUMIN, e_Jumin);
	DDX_Text(pDX, IDC_PERSON_ADDRESS, e_Address);
	DDX_Text(pDX, IDC_PERSON_PHONE1, e_Phone1);
	DDX_Text(pDX, IDC_PERSON_PHONE2, e_Phone2);
	DDX_Text(pDX, IDC_PERSON_DEPARTMENT, e_Department);
	DDX_Text(pDX, IDC_PERSON_POSITION, e_Position);
	DDX_Control(pDX, IDC_DB_SAVE, m_saveButton);
	DDX_Control(pDX, IDC_BACK, m_cancellButton);
	DDX_Control(pDX, IDC_DB_NEW, m_newButton);
	DDX_Text(pDX, IDC_PERSON_PAY, e_Pay);
	DDX_Text(pDX, IDC_PERSON_IPSA, e_Ipsa);
	DDX_Text(pDX, IDC_PERSON_FLAG, e_Flag);
	DDX_Text(pDX, IDC_PERSON_IPSA_DATE, e_IpsaDate);
	DDX_Text(pDX, IDC_PERSON_BAL_DATE, e_BalDate);
	DDX_Text(pDX, IDC_PERSON_PROMOTE_DATE, e_PromoteDate);
	DDX_Text(pDX, IDC_PERSON_ABSENCE_DATE, e_AbsenceDate);
	DDX_Text(pDX, IDC_PERSON_REINSTATEMENT_DATE, e_ReinstatementDate);
	DDX_Text(pDX, IDC_PERSON_RETIREMENT_DATE, e_RetirementDate);
	DDX_Text(pDX, IDC_PERSON_HEIGHT, e_Height);
	DDX_Text(pDX, IDC_PERSON_WEIGHT, e_Weight);
	DDX_Text(pDX, IDC_PERSON_EYE_L, e_EyeL);
	DDX_Text(pDX, IDC_PERSON_EYE_R, e_EyeR);
	DDX_Text(pDX, IDC_PERSON_BLOOD_T, e_Blood);
}


BEGIN_MESSAGE_MAP(Insa_Person_Info_Assign, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_PERSON_ID_NAME, GetDispInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PERSON_ID_NAME, &Insa_Person_Info_Assign::OnItemchangedPersonIdName)
	ON_BN_CLICKED(IDC_DB_NEW, &Insa_Person_Info_Assign::OnClickedDbNew)
	ON_BN_CLICKED(IDC_DB_SAVE, &Insa_Person_Info_Assign::OnClickedDbSave)
	ON_BN_CLICKED(IDC_BACK, &Insa_Person_Info_Assign::OnClickedBack)
END_MESSAGE_MAP()

#ifdef _DEBUG
void Insa_Person_Info_Assign::AssertValid() const
{
	CFormView::AssertValid();
}

void Insa_Person_Info_Assign::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Insa_Person_Info_Assign::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Insa_Person_Info_Assign::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Insa_Person_Info_Assign::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Insa_Person_Info_Assign::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Insa_Person_Info_Assign::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_dbList.DeleteAllItems();
	while (m_dbList.DeleteColumn(0));
	UpdateData(TRUE);

	
	
	
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	
	char* file = "Database.db";
	char* query = "SELECT ID, NAME FROM PERSON;";
		
	
	LVCOLUMN Col;
	pDoc->DB_GetTable(file, query, m_dbList, m_arTxts, Col);
	//pDoc->DB_GetTable(file, sql, m_dbList);
	
	file = NULL;





	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Insa_Person_Info_Assign::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Insa_Person_Info_Assign);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Insa_Person_Info_Assign::GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
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

void Insa_Person_Info_Assign::OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	if (p->uNewState != 0)
	{
		CString str= m_dbList.GetItemText(p->iItem, p->iSubItem);		
		m_nIndofList = p->iItem;
		char* tmp = pDoc->StringToChar(str);
		char* file = "Database.db";
		char* query = "SELECT * FROM PERSON WHERE ID = ";
		
		int strLen = strlen(query);
		int tmpLen = strlen(tmp);

		char* sql = new char[strLen+tmpLen +1];
		strcpy_s(sql, strLen+1, query);
		strcpy_s(sql + strLen,tmpLen+1,tmp);

		int rows, columns;
		char** result = pDoc->DB_GetTable(file, sql, rows, columns);

		e_Id = CString(result[columns]);
		e_Name = CString(result[1 + columns]);
		e_Jumin = CString(result[2 + columns]);
		e_Address = CString(result[3 + columns]);
		e_Phone1 = CString(result[4+ columns]);
		e_Phone2 = CString(result[5 + columns]);
		e_Department = CString(result[14 + columns]);
		e_Position = CString(result[15 + columns]);
		e_Pay = CString(result[6 + columns]);
		e_Ipsa = CString(result[7 + columns]);
		e_Flag = CString(result[21 + columns]);
		e_IpsaDate=CString(result[8+columns]);
		e_BalDate=CString(result[9+columns]);
		e_PromoteDate=CString(result[10+columns]);
		e_AbsenceDate=CString(result[11+columns]);
		e_ReinstatementDate=CString(result[12+columns]);
		e_RetirementDate=CString(result[13+columns]);
		e_Height=CString(result[16+columns]);
		e_Weight=CString(result[17+columns]);
		e_EyeL=CString(result[18+columns]);
		e_EyeR=CString(result[19+columns]);
		e_Blood=CString(result[20+columns]);

		format_in();

		UpdateData(FALSE);

		for (int i = 0; i <= rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				free(result[i*columns + j]);
			}
		}
		delete[] sql;
		free(result);
	}
	
	*pResult = 0;
}



void Insa_Person_Info_Assign::OnClickedDbNew()
{
	int index = m_dbList.GetItemCount();
	TRACE("index : %d\n",index);
	UpdateData(TRUE);
	
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char *fileName = "Database.db";
	char *query = "INSERT INTO PERSON (ID, NAME, JUMIN,ADDRESS, PHONE1, PHONE2, \
	PAY , IPSA, IPSA_DATE, BAL_DATE, PROMOTE_DATE ,ABSENCE_DATE ,REINSTATEMENT_DATE ,RETIREMENT_DATE , \
	DEPARTMENT, POSITION, HEIGHT, WEIGHT, EYE_L, EYE_R, BLOOD_T, FLAG) VALUES (";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery + 1];

	char* s = pDoc->DB_ConCat("%s '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');",
		query, pDoc->StringToChar(e_Id), pDoc->StringToChar(e_Name), pDoc->StringToChar(e_Jumin), pDoc->StringToChar(e_Address),
		pDoc->StringToChar(e_Phone1), pDoc->StringToChar(e_Phone2),
		pDoc->StringToChar(e_Pay), pDoc->StringToChar(e_Ipsa), pDoc->StringToChar(e_IpsaDate),
		pDoc->StringToChar(e_BalDate), pDoc->StringToChar(e_PromoteDate), pDoc->StringToChar(e_AbsenceDate),
		pDoc->StringToChar(e_ReinstatementDate), pDoc->StringToChar(e_ReinstatementDate),
		pDoc->StringToChar(e_Department), pDoc->StringToChar(e_Position), pDoc->StringToChar(e_Height),
		pDoc->StringToChar(e_Weight), pDoc->StringToChar(e_EyeL), pDoc->StringToChar(e_EyeR),
		pDoc->StringToChar(e_Blood), pDoc->StringToChar(e_Flag));
	
	pDoc->DB_SendQuery(fileName, s);



	m_dbList.DeleteAllItems();
	while (m_dbList.DeleteColumn(0));
	query = "SELECT ID, NAME FROM PERSON;";
	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, query, m_dbList, m_arTxts, Col);
	UpdateData(FALSE);


	m_dbList.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_dbList.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_dbList.EnsureVisible(index, FALSE);
	m_dbList.SetFocus();


}


void Insa_Person_Info_Assign::OnClickedDbSave()
{
	CString oldID = e_Id;
	int index = m_nIndofList;
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();
	char *fileName = "Database.db";
	char *query = "UPDATE PERSON SET ";
	int nLenQuery = strlen(query);
	char* buf = new char[nLenQuery+1];
		
	char* s = pDoc->DB_ConCat("%s ID='%s',NAME='%s',JUMIN='%s',ADDRESS='%s',PHONE1='%s',\
		PHONE2='%s',PAY='%s',IPSA='%s',IPSA_DATE='%s',BAL_DATE='%s',\
		PROMOTE_DATE='%s',ABSENCE_DATE='%s',REINSTATEMENT_DATE='%s',\
		RETIREMENT_DATE='%s',DEPARTMENT='%s',POSITION='%s',HEIGHT='%s',\
		WEIGHT='%s',EYE_L='%s',EYE_R='%s',BLOOD_T='%s',FLAG='%s' WHERE ID='%s';", 
		query, pDoc->StringToChar(e_Id), pDoc->StringToChar(e_Name), pDoc->StringToChar(e_Jumin), pDoc->StringToChar(e_Address),
		pDoc->StringToChar(e_Phone1), pDoc->StringToChar(e_Phone2),
		pDoc->StringToChar(e_Pay),pDoc->StringToChar( e_Ipsa),pDoc->StringToChar( e_IpsaDate),
		pDoc->StringToChar( e_BalDate),pDoc->StringToChar( e_PromoteDate),pDoc->StringToChar(e_AbsenceDate),
		pDoc->StringToChar( e_ReinstatementDate),pDoc->StringToChar(e_RetirementDate),
		pDoc->StringToChar(e_Department),pDoc->StringToChar( e_Position),pDoc->StringToChar( e_Height),
		pDoc->StringToChar( e_Weight),pDoc->StringToChar( e_EyeL),pDoc->StringToChar( e_EyeR),
		pDoc->StringToChar( e_Blood),pDoc->StringToChar( e_Flag), pDoc->StringToChar(oldID));
	
	
	pDoc->DB_SendQuery(fileName, s);
	
	

	m_dbList.DeleteAllItems();
	while (m_dbList.DeleteColumn(0));
	query = "SELECT ID, NAME FROM PERSON;";
	LVCOLUMN Col;
	pDoc->DB_GetTable(fileName, query, m_dbList, m_arTxts, Col);
	UpdateData(FALSE);
	m_dbList.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	m_dbList.SetItemState(index, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_dbList.EnsureVisible(index, FALSE);
	m_dbList.SetFocus();


}

void Insa_Person_Info_Assign::OnClickedBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	   
	UpdateData(FALSE);

}

void Insa_Person_Info_Assign::validcheck()
{

}

void Insa_Person_Info_Assign::format_in()
{
	CInsamanageDoc* pDoc = (CInsamanageDoc*)GetDocument();

	std::regex jumin("a");
	std::cmatch jumin_m;
	//char* jumin_s = pDoc->StringToChar(e_Jumin);
	char* jumin_s = "abc";
	//bool found = std::regex_match(jumin_s,jumin_s+strlen(jumin_s),jumin_m, jumin);
	const char *first = "abc";
	const char *last = first + strlen(first);
	std::cmatch narrowMatch;
	std::regex rx("a(b)c");

	bool found = regex_match(first, last, narrowMatch, rx);
	
	TRACE("%d %s %s %d\n", found, first, narrowMatch.str().c_str(),narrowMatch.length());
	//TRACE("%d jumin_s : %s, ma1 : %s, ma2 : %s, ma3 : %s\n",found, jumin_s, jumin_m[0], jumin_m[1].str(), jumin_m[2].str());
	e_Address = e_Address.Trim();
	
}