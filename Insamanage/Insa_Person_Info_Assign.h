#pragma once

#include <afxext.h>





class Insa_Person_Info_Assign : public CFormView
{

public:
	Insa_Person_Info_Assign();


	DECLARE_DYNCREATE(Insa_Person_Info_Assign)
	virtual ~Insa_Person_Info_Assign();

	// Form Data
public:
	enum { IDD = IDD_INSA_PERSON_INFO_ASSIGN };

	CListCtrl m_dbList;
	int		  m_nIndofList;
	CArray <CString, CString&> m_arTxts;
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
	
	void validcheck();
	void format_in();

	CString e_Id;
	CString e_Name;
	CString e_Jumin;
	CString e_Address;
	CString e_Phone1;
	CString e_Phone2;
	CString e_Department;
	CString e_Position;
	
	
	afx_msg void OnItemchangedPersonIdName(NMHDR *pNMHDR, LRESULT *pResult);
	
	CButton m_saveButton;
	CButton m_cancellButton;
	CButton m_newButton;
	afx_msg void OnClickedDbNew();
	afx_msg void OnClickedDbSave();
	afx_msg void OnClickedBack();
	CString e_Pay;
	CString e_Ipsa;
	CString e_Flag;
	CString e_IpsaDate;
	CString e_BalDate;
	CString e_PromoteDate;
	CString e_AbsenceDate;
	CString e_ReinstatementDate;
	CString e_RetirementDate;
	CString e_Height;
	CString e_Weight;
	CString e_EyeL;
	CString e_EyeR;
	CString e_Blood;
};

