#pragma once


// CMenuTree

class CMenuTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMenuTree)

public:
	CMenuTree();
	virtual ~CMenuTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
};


