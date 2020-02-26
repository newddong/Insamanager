
#pragma once

#include <afxext.h>





class TimeCard_Gen : public CFormView
{

public:
	TimeCard_Gen();


	DECLARE_DYNCREATE(TimeCard_Gen)
	virtual ~TimeCard_Gen();

	// Form Data
public:
	enum { IDD = IDD_TIMECARD_GEN };


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
	afx_msg void OnClickedPath();
	afx_msg void GetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedLoad();
	afx_msg void OnClickedGen();
	afx_msg void OnClickedButton();
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CArray <CString, CString&> m_arTxts;
	CArray <CString, CString&> m_arTxts2;
	CListCtrl m_erpFileList;
	CListCtrl m_erpList;
};

