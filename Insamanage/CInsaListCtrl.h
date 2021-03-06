#pragma once


// CInsaListCtrl

class CInsaListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CInsaListCtrl)

public:
	CInsaListCtrl();
	virtual ~CInsaListCtrl();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	CRect	m_SelectionRect;
	BOOL	m_SelectionFlag;
	CPoint  m_Point;
	int		m_Rows;
	int     m_Columns;
	int		m_PrevItem;

	//void OnInitialUpdate();
	void SetNoOfRows(int n = 0) { m_Rows = n; }
	void SetNoOfColumns(int n = 1) { m_Columns = n; }
	void SetStyles(DWORD dwStyle = LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};


