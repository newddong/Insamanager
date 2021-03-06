// CInsaListCtrl.cpp: 구현 파일
//

#include "stdafx.h"
#include "Insamanage.h"

#include "CInsaListCtrl.h"


// CInsaListCtrl

IMPLEMENT_DYNAMIC(CInsaListCtrl, CListCtrl)

CInsaListCtrl::CInsaListCtrl()
{

}

CInsaListCtrl::~CInsaListCtrl()
{
}

// CInsaListCtrl 메시지 처리기

BEGIN_MESSAGE_MAP(CInsaListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CInsaListCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsaListCtrl message handlers

void CInsaListCtrl::SetStyles(DWORD dwStyle)
{
	SetExtendedStyle(GetExtendedStyle() | dwStyle);
}

//void CInsaListCtrl::OnInitialUpdate()
//{
//	
//	int row, col;
//
//	LV_COLUMN lvc;
//	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//
//	// Insert Header columns
//	for (row = 0; row < m_Columns; row++)
//	{
//		lvc.iSubItem = row;
//		lvc.pszText = L"Columns";
//		lvc.cx = GetStringWidth(L"Columns") * 2;
//		lvc.fmt = LVCFMT_CENTER;
//		InsertColumn(row, &lvc);
//	}
//
//	// Insert First Column items for every row
//	LV_ITEM lvi;
//	lvi.mask = LVIF_TEXT | LVIF_STATE;
//
//	for (row = 0; row < m_Rows; row++)
//	{
//		char Buff[50];
//		
//		sprintf_s(Buff, sizeof(Buff), "Row %d", row);
//		lvi.iItem = row;
//		lvi.iSubItem = 0;
//		lvi.state = LVIS_SELECTED | LVIS_FOCUSED;
//		lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
//		lvi.pszText = (wchar_t*)Buff;
//		InsertItem(&lvi);
//
//
//		for (col = 1; col < m_Columns; col++)
//		{
//			sprintf_s(Buff,sizeof(Buff), "Col %d", col);
//			CString tmpbuf(Buff);
//			SetItemText(row, col, tmpbuf);
//		}
//	}
//}

void CInsaListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	TCHAR  lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = lpDrawItemStruct->itemID;
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));

	LV_COLUMN lvc, lvcprev;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;


	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nCol;
	if (!m_SelectionFlag)
	{
		for (nCol = 0; GetColumn(nCol, &lvc); nCol++)
		{
			if (nCol > 0)
			{
				GetSubItemRect(lpDrawItemStruct->itemID, nCol, LVIR_BOUNDS, m_SelectionRect);
			}
			else
			{
				GetItemRect(lpDrawItemStruct->itemID, m_SelectionRect, LVIR_BOUNDS);
				m_SelectionRect.right = GetColumnWidth(0);
				m_SelectionRect.left = 0;
			}
			if (m_SelectionRect.PtInRect(m_Point))
			{
				m_SelectionFlag = TRUE;
				//				TRACE("\n***%d,%d",lpDrawItemStruct->itemID,nCol);
				break;
			}
			else
				m_SelectionFlag = FALSE;

		}



		if ((lpDrawItemStruct->itemState & ODS_SELECTED) && m_SelectionFlag)
		{
			CRect rc = lpDrawItemStruct->rcItem;

			rc.left = m_SelectionRect.left;
			rc.right = m_SelectionRect.right;

			pDC->FillSolidRect(&rc, /*RGB(255, 0, 0));*/GetSysColor(COLOR_HIGHLIGHT)) ; 
			//pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		}
		else
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		}

	}

	for (nCol = 0; GetColumn(nCol, &lvc); nCol++)
	{
		if (nCol > 0)
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol - 1, &lvcprev);
			lpDrawItemStruct->rcItem.left += lvcprev.cx;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left;
		}

		// Get the text 
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));

		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

		UINT		uFormat = DT_LEFT;
		CString strlpBuf(lpBuffer);
		::DrawText(lpDrawItemStruct->hDC, lpBuffer, strlpBuf.GetLength(),
			&lpDrawItemStruct->rcItem, uFormat);

		pDC->SelectStockObject(SYSTEM_FONT);
	}

}

void CInsaListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_Point = point;
	m_SelectionFlag = FALSE;

	Invalidate();

	CListCtrl::OnLButtonDown(nFlags, point);
}

BOOL CInsaListCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | WS_BORDER;
	return CListCtrl::PreCreateWindow(cs);
}
