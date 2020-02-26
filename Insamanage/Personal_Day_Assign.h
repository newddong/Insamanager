#pragma once

#include <afxext.h>





class Personal_Day_Assign : public CFormView
{

public:
	Personal_Day_Assign();


	DECLARE_DYNCREATE(Personal_Day_Assign)
	virtual ~Personal_Day_Assign();

	// Form Data
public:
	enum { IDD = IDD_PERSONAL_DAY_ASSIGN };


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
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);

	CListCtrl m_dayList;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
	CDateTimeCtrl m_ctrDateTime;
	CDateTimeCtrl m_ctrDateTimeYr;
};

