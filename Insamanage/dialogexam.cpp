// dialogexam.cpp: 구현 파일
//

#include "stdafx.h"
#include "Insamanage.h"
#include "dialogexam.h"
#include "afxdialogex.h"


// dialogexam 대화 상자

IMPLEMENT_DYNAMIC(dialogexam, CDialogEx)

dialogexam::dialogexam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, edv(_T(""))
{

}

dialogexam::~dialogexam()
{
}

void dialogexam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, a);
	DDX_Control(pDX, IDC_EDIT1, edc);
	DDX_Text(pDX, IDC_EDIT1, edv);
}


BEGIN_MESSAGE_MAP(dialogexam, CDialogEx)
END_MESSAGE_MAP()


// dialogexam 메시지 처리기
