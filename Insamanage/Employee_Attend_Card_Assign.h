#pragma once

#include <afxext.h>





class Employee_Attend_Card_Assign : public CFormView
{

public:
	Employee_Attend_Card_Assign();


	DECLARE_DYNCREATE(Employee_Attend_Card_Assign)
	virtual ~Employee_Attend_Card_Assign();

	// Form Data
public:
	enum { IDD = IDD_EMPLOYEE_ATTEND_CARD_ASSIGN };


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

