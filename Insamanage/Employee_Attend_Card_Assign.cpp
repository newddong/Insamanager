#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Employee_Attend_Card_Assign.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Employee_Attend_Card_Assign, CFormView)

Employee_Attend_Card_Assign::Employee_Attend_Card_Assign() :CFormView(Employee_Attend_Card_Assign::IDD)
{
}


Employee_Attend_Card_Assign::~Employee_Attend_Card_Assign()
{
}

void Employee_Attend_Card_Assign::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Employee_Attend_Card_Assign, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void Employee_Attend_Card_Assign::AssertValid() const
{
	CFormView::AssertValid();
}

void Employee_Attend_Card_Assign::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Employee_Attend_Card_Assign::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Employee_Attend_Card_Assign::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Employee_Attend_Card_Assign::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Employee_Attend_Card_Assign::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Employee_Attend_Card_Assign::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Employee_Attend_Card_Assign::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Employee_Attend_Card_Assign);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
