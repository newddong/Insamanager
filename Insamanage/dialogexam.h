#pragma once


// dialogexam 대화 상자

class dialogexam : public CDialogEx
{
	DECLARE_DYNAMIC(dialogexam)

public:
	dialogexam(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~dialogexam();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl a;
	CEdit edc;
	CString edv;
};
