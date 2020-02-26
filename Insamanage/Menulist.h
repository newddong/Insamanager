#pragma once
#include <afxdockablepane.h>
#include "CMenuTree.h"

class Menulist :
	public CDockablePane
{
public:
	Menulist();
	virtual ~Menulist();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CMenuTree m_menuTree;
	CImageList m_menuTreeImage;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void FillTree();

	UINT findId(CString& str);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

