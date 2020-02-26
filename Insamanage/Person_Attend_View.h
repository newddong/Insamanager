
#pragma once

#include <afxext.h>





class Person_Attend_View : public CFormView
{

public:
	Person_Attend_View();


	DECLARE_DYNCREATE(Person_Attend_View)
	virtual ~Person_Attend_View();

	// Form Data
public:
	enum { IDD = IDD_PERSON_ATTEND_VIEW };


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
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult);
	

	CListCtrl m_personList;
	CListCtrl m_personAttList;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
	CArray <CString, CString&> m_arTxts2;
	CDateTimeCtrl m_ctrDateTime;
	CString e_Id, e_Name, e_Department, e_Position;
};

