#include "stdafx.h"


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Insamanage.h"
#endif
#include "InsamanageDoc.h"
#include "Insa_Person_Scholarship_Assign.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(Insa_Person_Scholarship_Assign, CFormView)

Insa_Person_Scholarship_Assign::Insa_Person_Scholarship_Assign() :CFormView(Insa_Person_Scholarship_Assign::IDD)
{
}


Insa_Person_Scholarship_Assign::~Insa_Person_Scholarship_Assign()
{
}

void Insa_Person_Scholarship_Assign::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Insa_Person_Scholarship_Assign, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

#ifdef _DEBUG
void Insa_Person_Scholarship_Assign::AssertValid() const
{
	CFormView::AssertValid();
}

void Insa_Person_Scholarship_Assign::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void Insa_Person_Scholarship_Assign::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//theApp.ShowPopupMenu(IDR_CONTEXT_MENU, point, this);
}

void Insa_Person_Scholarship_Assign::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:


	//ShowScrollBar(SB_HORZ, FALSE);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_DRAWFRAME);

}


BOOL Insa_Person_Scholarship_Assign::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void Insa_Person_Scholarship_Assign::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);

	pDC->DPtoLP(&rectClient);

	pDC->FillSolidRect(rectClient, ::GetSysColor(COLOR_3DFACE));
}


void Insa_Person_Scholarship_Assign::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();



	//CSize sizeTotal;
	// TODO: calculate the total size of this view

	SetScrollSizes(MM_TEXT, CSize(1200, 800));

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void Insa_Person_Scholarship_Assign::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect rect;
	//GetClientRect(&rect);
	//SetWindowPos(NULL, 0, 0, cx,cy, NULL);
	/*
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_LIST_Insa_Person_Scholarship_Assign);
	if (lst == NULL) {
		//AfxMessageBox(L"d");
		return;
	}
	*/
	//lst->SetWindowPos(NULL, 0, 0, 100, 100, NULL);


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
