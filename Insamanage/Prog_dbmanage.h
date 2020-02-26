#pragma once

#include <afxext.h>





class Prog_dbmanage : public CFormView
{

public:
	Prog_dbmanage();


	DECLARE_DYNCREATE(Prog_dbmanage)
	virtual ~Prog_dbmanage();

	// Form Data
public:
	enum { IDD = IDD_PROG_DBMANAGE };


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
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	char* StringToChar(CString str);
	CListCtrl m_dbList;
	CArray <CString,CString&> m_arTxts;

	
	CComboBox m_dbSelect;
	void init_dbSelect();

	void genDbfromTxt();
	void genDbFile();
	void genDbFileG2101();
	void genColumns();
	void genDbFileCODE1();
	void genDbFileCODE2();
	void genDbFileHOLYDAY();
	void loadFromTxt(CString &str, CFile &file, char*& tmp, long filepointer, int charlength);

	afx_msg void OnBnClickedGendb();
	afx_msg void OnClickedDbview();
	afx_msg void OnBnClickedTextview();
	
	afx_msg void OnSelchangeTableselect();
	// //SQL Select Sqeury 적는 부분
	CSqlEdit m_ctrlSqlEdit;
};

