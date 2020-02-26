#pragma once

#include <afxext.h>





class Code_Personpay_List : public CFormView
{

public:
	Code_Personpay_List();


	DECLARE_DYNCREATE(Code_Personpay_List)
	virtual ~Code_Personpay_List();

	// Form Data
public:
	enum { IDD = IDD_CODE_PERSONPAY_LIST };

	CListCtrl m_code1List;
	CListCtrl m_code2List;
	int		  m_nIndofList;
	int		  m_nIndofList2;
	CArray <CString, CString&> m_arTxts;
	CArray <CString, CString&> m_arTxts2;

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
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedPersonIdName2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedBack();
	afx_msg void OnClickedNew2();
	afx_msg void OnClickedNew();
	afx_msg void OnClickedEdit();
	afx_msg void OnClickedEdit2();
	afx_msg void OnClickedDelete();
	afx_msg void OnClickedDelete2();



	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CString e_code1, e_code2, e_code1_name, e_code2_name;

	
};

