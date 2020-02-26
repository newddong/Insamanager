#pragma once

#include <afxext.h>





class Mon_HolyDay_Check : public CFormView
{

public:
	Mon_HolyDay_Check();


	DECLARE_DYNCREATE(Mon_HolyDay_Check)
	virtual ~Mon_HolyDay_Check();

	// Form Data
public:
	enum { IDD = IDD_MON_HOLYDAY_CHECK };


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

