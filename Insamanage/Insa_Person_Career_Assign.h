#pragma once

#include <afxext.h>





class Insa_Person_Career_Assign : public CFormView
{

public:
	Insa_Person_Career_Assign();


	DECLARE_DYNCREATE(Insa_Person_Career_Assign)
	virtual ~Insa_Person_Career_Assign();

	// Form Data
public:
	enum { IDD = IDD_INSA_PERSON_CAREER_ASSIGN };


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

