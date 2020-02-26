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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDockablePane::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


int Menulist::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	CRect emptyRect;
	emptyRect.SetRectEmpty();

	const DWORD style = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_menuTree.Create(style, emptyRect, this, 3))
	{
		TRACE0("�޴� Ʈ�� ���� ����");
		return -1;
	}


	m_menuTreeImage.DeleteImageList();
	UINT uiBmpId = IDB_CLASS_VIEW_24;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(L"��Ʈ�� �ε� ����. %x\n",uiBmpId);
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
	HTREEITEM hRoot = m_menuTree.InsertItem(L"���彺�����", 0, 0);
	m_menuTree.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSubmenu = m_menuTree.InsertItem(L"�λ����", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"�λ�⺻���� ���", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"�����̷�ī�� ���", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"�����з»��� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�μ������������ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���κ��ټӿ�����ȸ", 2, 2, hSubmenu);

	m_menuTree.Expand(hRoot, TVE_EXPAND);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);

	hSubmenu = m_menuTree.InsertItem(L"�ϱ��� ����", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"TIME-CARD ����", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���ϱ��³��� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"��ٺ��̻��� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"����� �ϱ��� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���κ� ��ٺ� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�����ܾ��ð� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�μ��� ��ٺ� ����Ʈ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�μ��� �ϱ��� ����", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�޹��� ���� ���", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"��������޹� ���", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"������ī�� ���", 2, 2, hSubmenu);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);
	
	hSubmenu = m_menuTree.InsertItem(L"������ ����", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"�������ڷ� ����", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�����߻��۾�", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�����³��� ������ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�������ܾ��ð� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"������ ȸ���ڷ� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���κ� ����ٺ� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"����ٺ� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"����/���� ����ٺ�", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���� �������� ��ȸ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�μ��� �ϱ��� ����", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"������ȸ/����", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�����Ȯ��", 2, 2, hSubmenu);
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);

	hSubmenu = m_menuTree.InsertItem(L"�޿����ʰ���", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"���κ� �����޿� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���������� ������", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���������� ������", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"���°��� �޿� ����Ʈ", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);


	hSubmenu = m_menuTree.InsertItem(L"�����ڵ����", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	//m_menuTree.InsertItem(L"�λ�, �޿��ڵ� ���", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"�λ�, �޿��ڵ� ����Ʈ", 2, 2, hSubmenu);
	m_menuTree.InsertItem(L"ȸ��⺻���� ���", 2, 2, hSubmenu);
	//m_menuTree.InsertItem(L"�����ȣ�� ���", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);


	hSubmenu = m_menuTree.InsertItem(L"���α׷�����", 1, 1, hRoot);
	m_menuTree.SetItemState(hSubmenu, TVIS_BOLD, TVIS_BOLD);
	m_menuTree.InsertItem(L"���κ� �н����� ����", 2, 2, hSubmenu);
	
	m_menuTree.Expand(hSubmenu, TVE_EXPAND);
}


void Menulist::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CTreeCtrl* menuT = (CTreeCtrl*)&m_menuTree;
	UINT flags = 0;
	CPoint ptTree = point;
	menuT->ScreenToClient(&ptTree);
	HTREEITEM selectedItem = menuT->HitTest(ptTree, &flags);
	CString ItemText = menuT->GetItemText(selectedItem);
	


	TRACE(L"%s����%d,%d\n", ItemText,point.x, point.y);
		
	





	CDockablePane::OnLButtonDblClk(nFlags, point);



}


BOOL Menulist::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	NMHDR* pNmhdr = (NMHDR*)lParam;
	CString str;
	HTREEITEM selectedItem;
	UINT nID;
	CMainFrame* pMfrm = (CMainFrame*)AfxGetMainWnd();
	if (pMfrm == NULL)
	{
		//TRACE("���������� ��\n");
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
	
	//�λ����
	if(str==L"�λ�⺻���� ���"){
		return ID_32771;
	}

	if(str==L"�����̷�ī�� ���"){
		return ID_32772;
	}

	if(str==L"�����з»��� ���"){
		return ID_32773;
	}

	if(str==L"�μ������������ȸ"){
		return ID_32774;
	}

	if(str==L"���κ��ټӿ�����ȸ"){
		return ID_32775;
	}


	//�ϱ��� ����
	if(str==L"TIME-CARD ����"){
		return ID_32776;
	}

	if(str==L"���ϱ��³��� ���"){
		return ID_32777;
	}

	if(str==L"��ٺ��̻��� ��ȸ"){
		return ID_32778;
	}

	if(str==L"����� �ϱ��� ��ȸ"){
		return ID_32779;
	}

	if(str==L"���κ� ��ٺ� ��ȸ"){
		return ID_32780;
	}

	if(str==L"�����ܾ��ð� ��ȸ"){
		return ID_32781;
	}

	if(str==L"�μ��� ��ٺ� ����Ʈ"){
		return ID_32782;
	}

	if(str==L"�μ��� �ϱ��� ����"){
		return ID_32783;
	}

	if(str==L"�޹��� ���� ���"){
		return ID_32784;
	}

	if(str==L"��������޹� ���"){
		return ID_32785;
	}

	if(str==L"������ī�� ���"){
		return ID_32786;
	}


	//������ ����
	if(str==L"�������ڷ� ����"){
		return ID_32787;
	}

	if(str==L"�����߻��۾�"){
		return ID_32788;
	}

	if(str==L"�����³��� ������ȸ"){
		return ID_32789;
	}

	if(str==L"�������ܾ��ð� ��ȸ"){
		return ID_32790;
	}

	if(str==L"������ ȸ���ڷ� ���"){
		return ID_32791;
	}

	if(str==L"���κ� ����ٺ� ���"){
		return ID_32792;
	}

	if(str==L"����ٺ� ���"){
		return ID_32793;
	}

	if(str==L"����/���� ����ٺ�"){
		return ID_32794;
	}

	if(str==L"���� �������� ��ȸ"){
		return ID_32795;
	}

	if(str==L"�μ��� �ϱ��� ����"){
		return ID_32796;
	}

	if(str==L"������ȸ/����"){
		return ID_32797;
	}

	if(str==L"�����Ȯ��"){
		return ID_32798;
	}


	//�޿����ʰ���
	if(str==L"���κ� �����޿� ���"){
		return ID_32801;
	}

	if(str==L"���������� ������"){
		return ID_32802;
	}

	if(str==L"���������� ������"){
		return ID_32803;
	}

	if(str==L"���°��� �޿� ����Ʈ"){
		return ID_32804;
	}


	//�����ڵ����

	if(str==L"�λ�, �޿��ڵ� ���"){
		return ID_32805;
	}

	if(str==L"�λ�, �޿��ڵ� ����Ʈ"){
		return ID_32806;
	}

	if(str==L"ȸ��⺻���� ���"){
		return ID_32807;
	}

	if(str==L"�����ȣ�� ���"){
		return ID_32808;
	}



	//���α׷�����

	if(str==L"���κ� �н����� ����"){
		return ID_32810;
	}

	if(str==L"�����ͺ��̽� ����"){
		return ID_32811;
	}

	
}