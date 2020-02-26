#pragma once

#include <afxext.h>





class Chulgeun_isang :	public CFormView
{
	
public:
	Chulgeun_isang();
	
	
	DECLARE_DYNCREATE(Chulgeun_isang)
	virtual ~Chulgeun_isang();
	
	// Form Data
public:
	enum {IDD=IDD_CHULGEUN_ISANG};


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
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void RadioCtrl(UINT id);
	afx_msg void RadioCtrl2(UINT id);

	CListCtrl m_ctrChul;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
	CDateTimeCtrl m_ctrDateTime;

	UINT radio_pay;
	UINT radio_sex;

	
};

