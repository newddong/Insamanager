#include "stdafx.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Insa_Person_Work_Year.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Insa_Person_Work_Year, CFormView)

Insa_Person_Work_Year::Insa_Person_Work_Year() :CFormView(Insa_Person_Work_Year::IDD)
{
}


Insa_Person_Work_Year::~Insa_Person_Work_Year()
{
}

void Insa_Person_Work_Year::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Insa_Person_Work_Year, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void Insa_Person_Work_Year::AssertValid() const
{
	CFormView::AssertValid();
}

void Insa_Person_Work_Year::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Insa_Person_Work_Year::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Insa_Person_Work_Year::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Insa_Person_Work_Year::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Insa_Person_Work_Year::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Insa_Person_Work_Year::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void Insa_Person_Work_Year::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Insa_Person_Work_Year);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
