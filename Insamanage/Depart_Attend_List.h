#pragma once

#include <afxext.h>





class Depart_Attend_List : public CFormView
{

public:
	Depart_Attend_List();


	DECLARE_DYNCREATE(Depart_Attend_List)
	virtual ~Depart_Attend_List();

	// Form Data
public:
	enum { IDD = IDD_DEPART_ATTEND_LIST };


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

	CComboBox m_ctrlDep;
	CListCtrl m_ctrEmployee;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
	afx_msg void OnSelchangeDepartment();

};


