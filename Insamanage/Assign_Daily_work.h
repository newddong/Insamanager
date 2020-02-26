#pragma once

#include <afxext.h>





class Assign_Daily_work : public CFormView
{

public:
	Assign_Daily_work();


	DECLARE_DYNCREATE(Assign_Daily_work)
	virtual ~Assign_Daily_work();

	// Form Data
public:
	enum { IDD = IDD_ASSIGN_DAILY_WORK	};

	CListCtrl m_personList;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
	CDateTimeCtrl m_ctrDateTime;
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
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult);

	CString e_Id, e_Name, e_Department, e_Position, e_Janup, e_Tjanup, e_Jigak;
	CString e_Guencode, e_Chuldate, e_Backhomedate, e_Outtime, e_Editdate;


	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
};

