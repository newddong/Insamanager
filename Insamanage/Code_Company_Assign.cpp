#include "stdafx.h"


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Code_Company_Assign.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Code_Company_Assign, CFormView)

Code_Company_Assign::Code_Company_Assign() :CFormView(Code_Company_Assign::IDD)
{
}


Code_Company_Assign::~Code_Company_Assign()
{
}

void Code_Company_Assign::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Code_Company_Assign, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void Code_Company_Assign::AssertValid() const
{
	CFormView::AssertValid();
}

void Code_Company_Assign::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Code_Company_Assign::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Code_Company_Assign::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Code_Company_Assign::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Code_Company_Assign::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Code_Company_Assign::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void Code_Company_Assign::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Code_Company_Assign);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}