// CMenuTree.cpp: 구현 파일
//

#include "stdafx.h"
#include "Insamanage.h"
#include "CMenuTree.h"


// CMenuTree

IMPLEMENT_DYNAMIC(CMenuTree, CTreeCtrl)

CMenuTree::CMenuTree()
{

}

CMenuTree::~CMenuTree()
{
}


BEGIN_MESSAGE_MAP(CMenuTree, CTreeCtrl)
	
	ON_WM_LBUTTONDBLCLK()
	
END_MESSAGE_MAP()



// CMenuTree 메시지 처리기





void CMenuTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UINT flags = 0;
	CPoint ptTree = point;
	this->ScreenToClient(&ptTree);
	HTREEITEM selectedItem = this->GetSelectedItem();
	CString ItemText = this->GetItemText(selectedItem);

	
	
	TRACE(_T("%s클릭%d,%d\n"), ItemText, point.x, point.y);


	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

