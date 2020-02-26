#include "stdafx.h"
#include "MainFrm.h"
#include "resource.h"
#include "Menulist.h"


Menulist::Menulist()
{
}


Menulist::~Menulist()
{
}
BEGIN_MESSAGE_MAP(Menulist, CDockablePane)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void Menulist::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_menuTree.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOZORDER);

}


void Menulist::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDockablePane::OnPaint()을(를) 호출하지 마십시오.
}


int Menulist::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CRect emptyRect;
	emptyRect.SetRectEmpty();

	const DWORD style = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_menuTree.Create(style, emptyRect, this, 3))
	{
		TRACE0("메뉴 트리 생성 실패");
		return -1;
	}


	m_menuTreeImage.DeleteImageList();
	UINT uiBmpId = IDB_CLASS_VIEW_24;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(L"비트맵 로드 실패. %x\n",uiBmpId);
		ASSERT(FALSE);
		return -1;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK|ILC_COLOR24;


	m_menuTreeImage.Create(16,bmpObj.bmHeight,nFlags,0,0);
	m_menuTreeImage.Add(&bmp, RGB(255, 0, 0));

	m_menuTree.SetImageList(&m_menuTreeImage, TVSIL_NORMAL);


	FillTree();

	return 0;
	
}


void Menulist::FillTree()
{
	HTREEITEM hRoot = m_menuTree.InsertItem(L"슈펙스비앤피", 0, 0);
	m_menuTree.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSubmenu = m_menuTree.InsertItem(L"인사관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"인사기본사항 등록", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"개인이력카드 등록", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"최종학력사항 등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"부서별사원내역조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"개인별근속연수조회", 2, 2, hSubmenu);

	m_menuTree.Expand(hRoot, TVE_EXPAND);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);

	hSubmenu = m_menuTree.InsertItem(L"일근태 관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"TIME-CARD 생성", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"일일근태내역 등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"출근부이상자 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"사번별 일근태 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"개인별 출근부 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"근태잔업시간 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"부서별 출근부 리스트", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"부서별 일구간 근태", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"휴무일 내역 등록", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"격주토요휴무 등록", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"사원출근카드 등록", 2, 2, hSubmenu);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);
	
	hSubmenu = m_menuTree.InsertItem(L"월근태 관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"월근태자료 생성", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월차발생작업", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월근태내역 수정조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월근태잔업시간 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월근태 회람자료 출력", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"개인별 월출근부 출력", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월출근부 출력", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"부장/차장 월출근부", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월별 월차내역 조회", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"부서별 일구간 근태", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"월차조회/수정", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"년월차확인", 2, 2, hSubmenu);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);

	hSubmenu = m_menuTree.InsertItem(L"급여기초관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"개인별 월정급여 등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"고정공제및 수당등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"가변공제및 수당등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"근태관련 급여 리스트", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);


	hSubmenu = m_menuTree.InsertItem(L"기초코드관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	//m_menuTree.InsertItem(L"인사, 급여코드 등록", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"인사, 급여코드 리스트", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"회사기본내역 등록", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"우편번호부 등록", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);


	hSubmenu = m_menuTree.InsertItem(L"프로그램관리", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"개인별 패스워드 관리", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);
}


void Menulist::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTreeCtrl* menuT = (CTreeCtrl*)&m_menuTree;
	UINT flags = 0;
	CPoint ptTree = point;
	menuT->ScreenToClient(&ptTree);
	HTREEITEM selectedItem = menuT->HitTest(ptTree, &flags);
	CString ItemText = menuT->GetItemText(selectedItem);
	


	TRACE(L"%s추적%d,%d\n", ItemText,point.x, point.y);
		
	





	CDockablePane::OnLButtonDblClk(nFlags, point);



}


BOOL Menulist::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	NMHDR* pNmhdr = (NMHDR*)lParam;
	CString str;
	HTREEITEM selectedItem;
	UINT nID;
	CMainFrame* pMfrm = (CMainFrame*)AfxGetMainWnd();
	if (pMfrm == NULL)
	{
		//TRACE("메인프레임 널\n");
	}
	
	


	if (pNmhdr->code == -3) {
		selectedItem = m_menuTree.GetSelectedItem();
		str = m_menuTree.GetItemText(selectedItem);
		nID = findId(str);
		
		pMfrm->MenuClick(nID);

		
	}
	
	
	
	

	//TRACE(L"wParam : %d, code : %d,  hwnd : %d, id : %d %s\n",wParam, pNmhdr->code, pNmhdr->hwndFrom, pNmhdr->idFrom,str);


	return CDockablePane::OnNotify(wParam, lParam, pResult);
}

UINT Menulist::findId(CString& str)
{
	
	//인사관리
	if(str==L"인사기본사항 등록"){
		return ID_32771;
	}

	if(str==L"개인이력카드 등록"){
		return ID_32772;
	}

	if(str==L"최종학력사항 등록"){
		return ID_32773;
	}

	if(str==L"부서별사원내역조회"){
		return ID_32774;
	}

	if(str==L"개인별근속연수조회"){
		return ID_32775;
	}


	//일근태 관리
	if(str==L"TIME-CARD 생성"){
		return ID_32776;
	}

	if(str==L"일일근태내역 등록"){
		return ID_32777;
	}

	if(str==L"출근부이상자 조회"){
		return ID_32778;
	}

	if(str==L"사번별 일근태 조회"){
		return ID_32779;
	}

	if(str==L"개인별 출근부 조회"){
		return ID_32780;
	}

	if(str==L"근태잔업시간 조회"){
		return ID_32781;
	}

	if(str==L"부서별 출근부 리스트"){
		return ID_32782;
	}

	if(str==L"부서별 일구간 근태"){
		return ID_32783;
	}

	if(str==L"휴무일 내역 등록"){
		return ID_32784;
	}

	if(str==L"격주토요휴무 등록"){
		return ID_32785;
	}

	if(str==L"사원출근카드 등록"){
		return ID_32786;
	}


	//월근태 관리
	if(str==L"월근태자료 생성"){
		return ID_32787;
	}

	if(str==L"월차발생작업"){
		return ID_32788;
	}

	if(str==L"월근태내역 수정조회"){
		return ID_32789;
	}

	if(str==L"월근태잔업시간 조회"){
		return ID_32790;
	}

	if(str==L"월근태 회람자료 출력"){
		return ID_32791;
	}

	if(str==L"개인별 월출근부 출력"){
		return ID_32792;
	}

	if(str==L"월출근부 출력"){
		return ID_32793;
	}

	if(str==L"부장/차장 월출근부"){
		return ID_32794;
	}

	if(str==L"월별 월차내역 조회"){
		return ID_32795;
	}

	if(str==L"부서별 일구간 근태"){
		return ID_32796;
	}

	if(str==L"월차조회/수정"){
		return ID_32797;
	}

	if(str==L"년월차확인"){
		return ID_32798;
	}


	//급여기초관리
	if(str==L"개인별 월정급여 등록"){
		return ID_32801;
	}

	if(str==L"고정공제및 수당등록"){
		return ID_32802;
	}

	if(str==L"가변공제및 수당등록"){
		return ID_32803;
	}

	if(str==L"근태관련 급여 리스트"){
		return ID_32804;
	}


	//기초코드관리

	if(str==L"인사, 급여코드 등록"){
		return ID_32805;
	}

	if(str==L"인사, 급여코드 리스트"){
		return ID_32806;
	}

	if(str==L"회사기본내역 등록"){
		return ID_32807;
	}

	if(str==L"우편번호부 등록"){
		return ID_32808;
	}



	//프로그램관리

	if(str==L"개인별 패스워드 관리"){
		return ID_32810;
	}

	if(str==L"데이터베이스 관리"){
		return ID_32811;
	}

	
}