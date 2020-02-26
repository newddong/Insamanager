#pragma once

#include <afxext.h>





class Mon_HolyDay_Viewedit : public CFormView
{

public:
	Mon_HolyDay_Viewedit();


	DECLARE_DYNCREATE(Mon_HolyDay_Viewedit)
	virtual ~Mon_HolyDay_Viewedit();

	// Form Data
public:
	enum { IDD = IDD_MON_HOLYDAY_VIEWEDIT };


	// Attributes
public:

	// Operations
public:

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);

	// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

