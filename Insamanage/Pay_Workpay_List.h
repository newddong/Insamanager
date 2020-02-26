#pragma once

#include <afxext.h>





class Pay_Workpay_List : public CFormView
{

public:
	Pay_Workpay_List();


	DECLARE_DYNCREATE(Pay_Workpay_List)
	virtual ~Pay_Workpay_List();

	// Form Data
public:
	enum { IDD = IDD_PAY_WORKPAY_LIST };


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

