
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Insamanage.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "Chulgeun_isang.h"
#include "Assign_Daily_work.h"
#include "Biweekend_SaturDay.h"
#include "Daily_Work_View.h"
#include "Depart_Attend_Daily.h"
#include "Depart_Attend_List.h"
#include "Employee_Attend_Card_Assign.h"
#include "Overtime_View.h"
#include "Person_Attend_View.h"
#include "Personal_Day_Assign.h"
#include "TimeCard_Gen.h"
#include "Code_Company_Assign.h"
#include "Code_Personpay_Assign.h"
#include "Code_Personpay_List.h"
#include "Code_Postnum_Assign.h"
#include "Insa_Dep_Employee_View.h"
#include "Insa_Person_Career_Assign.h"
#include "Insa_Person_Info_Assign.h"
#include "Insa_Person_Scholarship_Assign.h"
#include "Insa_Person_Work_Year.h"
#include "Mon_Attend_Print.h"
#include "Mon_Dep_Daily_Att.h"
#include "Mon_HolyDay_Check.h"
#include "Mon_HolyDay_Gen.h"
#include "Mon_HolyDay_View.h"
#include "Mon_HolyDay_Viewedit.h"
#include "Mon_Manager_Attend_View.h"
#include "Mon_Overwork_View.h"
#include "Mon_Person_Attend_Print.h"
#include "Mon_Work_Data_Gen.h"
#include "Mon_Work_Edit_View.h"
#include "Mon_Work_Print.h"
#include "Pay_Deduct_Extra_Assign.h"
#include "Pay_Person_Monpay_Assign.h"
#include "Pay_Var_Deduct_Extra_Assign.h"
#include "Pay_Workpay_List.h"
#include "Prog_dbmanage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND_RANGE(ID_32771,ID_32811, &CMainFrame::MenuClick)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_bitmap.LoadBitmapW(IDB_FRMBACKGROUND);

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 사용할 수 있는 다른 스타일...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // FALSE로 설정하여 탭 영역 오른쪽에 닫기 단추를 배치합니다.
	mdiTabParams.m_bTabIcons = FALSE;    // TRUE로 설정하여 MDI 탭의 문서 아이콘을 활성화합니다.
	mdiTabParams.m_bAutoColor = TRUE;    // FALSE로 설정하여 MDI 탭의 자동 색 지정을 비활성화합니다.
	mdiTabParams.m_bDocumentMenu = TRUE; // 탭 영역의 오른쪽 가장자리에 문서 메뉴를 활성화합니다.
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("메뉴 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	

	// 메뉴 모음을 활성화해도 포커스가 이동하지 않게 합니다.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	
	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	
	/*if (!m_insaMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_insaMenuBar.LoadToolBar(IDR_INSA_MANAGE))
	{
		TRACE0("인사메뉴 생성을 실패했습니다.\n");
		
	}*/

	//CString strToolBarName;
	//bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	//ASSERT(bNameValid);
	//m_wndToolBar.SetWindowText(strToolBarName);

	/*CString insaName;
	insaName = "인사메뉴";
	m_insaMenuBar.SetWindowTextW(insaName);*/


	//CString strCustomize;
	//bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	//m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 사용자 정의 도구 모음 작업을 허용합니다.
	//InitUserToolbars(nullptr, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음 및 메뉴 모음을 도킹할 수 없게 하려면 이 다섯 줄을 삭제하십시오.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_insaMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	//DockPane(&m_insaMenuBar);
	//DockPane(&m_wndToolBar);


	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 메뉴 항목 이미지를 로드합니다(표준 도구 모음에 없음).
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 도킹 창을 만듭니다.
	if (!CreateDockingWindows())
	{
		TRACE0("도킹 창을 만들지 못했습니다.\n");
		return -1;
	}

	//m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	m_insaMenuList.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndFileView);
	DockPane(&m_insaMenuList);
	//CDockablePane* pTabbedBar = nullptr;
	//m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	//m_insaMenuList.AttachToTabWnd(&m_wndClassView, DM_SHOW, TRUE, &pTabbedBar);
	//m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndOutput);
	//m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndProperties);

	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	// 향상된 창 관리 대화 상자를 활성화합니다.
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 도구 모음 및 도킹 창 메뉴 바꾸기를 활성화합니다.
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 빠른(<Alt> 키를 누른 채 끌기) 도구 모음 사용자 지정을 활성화합니다.
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == nullptr)
	{
		// 사용자 정의 도구 모음 이미지를 로드합니다.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 메뉴 개인 설정을 활성화합니다(가장 최근에 사용한 명령).
	// TODO: 사용자의 기본 명령을 정의하여 각 풀다운 메뉴에 하나 이상의 기본 명령을 포함시킵니다.
	CList<UINT, UINT> lstBasicCommands;

	/*lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);*/

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// 창 제목 표시줄에서 문서 이름 및 응용 프로그램 이름의 순서를 전환합니다.
	// 문서 이름이 축소판 그림과 함께 표시되므로 작업 표시줄의 기능성이 개선됩니다.
	ModifyStyle(0, FWS_PREFIXTITLE);
	initViewList();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	/*
	// 클래스 뷰를 만듭니다.
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("클래스 뷰 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}

	// 파일 뷰를 만듭니다.
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("파일 뷰 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}

	// 출력 창을 만듭니다.
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}

	// 속성 창을 만듭니다.
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("속성 창을 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}

	
	*/
	
	if (!m_insaMenuList.Create(_T("메뉴"), this, CRect(0, 0, 250, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("메뉴리스트를 만들지 못했습니다.\n");
		return FALSE; // 만들지 못했습니다.
	}



	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	/*
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);
	*/
	UpdateMDITabbedBarsIcons();
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 메뉴를 검색합니다. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	//m_wndOutput.UpdateFonts();
	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// 기본 클래스가 실제 작업을 수행합니다.

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 모든 사용자 도구 모음에 사용자 지정 단추를 활성화합니다.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != nullptr)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}

void CMainFrame::MenuClick(UINT nID)
{
	HMENU m = m_wndMenuBar.GetDefaultMenu();
	CMenu* menu = CMenu::FromHandle(m);

	if (menu == NULL)
	{
		return;
	}
	CString menustr;
	menu->GetMenuStringW(nID, menustr, MF_BYCOMMAND);
	   
	POSITION pTmpl = theApp.GetFirstDocTemplatePosition();
	if (pTmpl == NULL)
	{
		TRACE("탬플릿 없음\n");
		return;
	}

	CMultiDocTemplate* pTmp = (CMultiDocTemplate*)theApp.GetNextDocTemplate(pTmpl);
	CChildFrame* cFrm = (CChildFrame*)this->GetActiveFrame();
	CDocument* pDoc = cFrm->GetActiveDocument();
	
	
	

	if (pDoc == NULL)
	{
		pDoc = pTmp->CreateNewDocument();
	}

	if (pDoc != NULL)
		ASSERT_VALID(pDoc);
	
	CCreateContext context;
	context.m_pCurrentFrame = GetActiveFrame();
	context.m_pCurrentDoc = pDoc;
	m_viewList.Lookup(nID, context.m_pNewViewClass);
	context.m_pNewDocTemplate = pTmp;
	
	CChildFrame* pFrame = new CChildFrame;
	
	// create new from resource
	if (!pFrame->LoadFrame(IDR_INSA_MANAGE,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
		NULL, &context))
	{
		TRACE(traceAppMsg, 0, "Warning: CDocTemplate couldn't create a frame.\n");
		// frame will be deleted in PostNcDestroy cleanup
		return;
	}
		
	pDoc->m_bAutoDelete = FALSE;

	if (pFrame == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return;
	}
	ASSERT_VALID(pFrame);
	
	CView* pView = NULL;
	if (pFrame->GetActiveView() == NULL)
	{
		CWnd* pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
		if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CView)))
		{
			pView = (CView*)pWnd;
			pFrame->SetActiveView(pView, FALSE);

		}
	}

	// send initial update to all views (and other controls) in the frame
	pFrame->SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

	// give view a chance to save the focus (CFormView needs this)
	//if (pView != NULL)
		//pView->OnActivateFrame(WA_INACTIVE, this);

	// finally, activate the frame
	// (send the default show command unless the main desktop window)
	int nCmdShow = -1;      // default
	CWinApp* pApp = AfxGetApp();

	if (pApp != NULL && pApp->m_pMainWnd == this)
	{

		nCmdShow = pApp->m_nCmdShow; // use the parameter from WinMain
		pApp->m_nCmdShow = -1; // set to default after first time
	}

	pFrame->ActivateFrame(nCmdShow);
	if (pView != NULL)
	{
		//pView->OnActivateView(TRUE, pView, pView);
		UNUSED(pView);   // unused in release builds

		//ASSERT(pView == this);

		// take the focus if this frame/view/pane is now active
		if (pView->IsTopParentActive())
			pView->SetFocus();
	}
	// update frame counts and frame title (may already have been visible)
	if (pDoc != NULL)
		pDoc->UpdateFrameCounts();
		
	pFrame->SetWindowTextW(menustr);
	TRACE(_T("%s\n"), menustr);
	AfxSetWindowText(m_hWnd, (LPCTSTR)L"슈펙스 비앤피 인사관리");

	delete pTmpl, pTmp, cFrm, pDoc,pFrame,pApp,pView;
	//menu->DestroyMenu();
	

	

}

void CMainFrame::initViewList()
{
	//인사관리
	m_viewList.SetAt(ID_32771, RUNTIME_CLASS(Insa_Person_Info_Assign));			//인사기본사항 등록
	m_viewList.SetAt(ID_32772, RUNTIME_CLASS(Insa_Person_Career_Assign));			//개인이력카드 등록
	m_viewList.SetAt(ID_32773, RUNTIME_CLASS(Insa_Person_Scholarship_Assign));			//최종학력사항 등록
	m_viewList.SetAt(ID_32774, RUNTIME_CLASS(Insa_Dep_Employee_View));			//부서별사원내역조회
	m_viewList.SetAt(ID_32775, RUNTIME_CLASS(Insa_Person_Work_Year));			//개인별근속연수조회
	
	//일근태 관리
	m_viewList.SetAt(ID_32776, RUNTIME_CLASS(TimeCard_Gen));			//TIME-CARD생성
	m_viewList.SetAt(ID_32777, RUNTIME_CLASS(Assign_Daily_work));		//일일근태내역 등록
	m_viewList.SetAt(ID_32778, RUNTIME_CLASS(Chulgeun_isang));			//출근부이상자 조회
	m_viewList.SetAt(ID_32779, RUNTIME_CLASS(Daily_Work_View));			//사번별 일근태 조회
	m_viewList.SetAt(ID_32780, RUNTIME_CLASS(Person_Attend_View));		//개인별 출근부 조회
	m_viewList.SetAt(ID_32781, RUNTIME_CLASS(Overtime_View));			//근태잔업시간 조회
	m_viewList.SetAt(ID_32782, RUNTIME_CLASS(Depart_Attend_List));		//부서별 출근부 리스트
	m_viewList.SetAt(ID_32783, RUNTIME_CLASS(Depart_Attend_Daily));		//부서별 일구간 근태
	m_viewList.SetAt(ID_32784, RUNTIME_CLASS(Personal_Day_Assign));		//휴무일 내역 등록
	m_viewList.SetAt(ID_32785, RUNTIME_CLASS(Biweekend_SaturDay));		//격주토요휴무 등록
	m_viewList.SetAt(ID_32786, RUNTIME_CLASS(Employee_Attend_Card_Assign)); //사원출근카드 등록
	
	//월근태 관리
	m_viewList.SetAt(ID_32787, RUNTIME_CLASS(Mon_Work_Data_Gen));			//월근태자료  생성
	m_viewList.SetAt(ID_32788, RUNTIME_CLASS(Mon_HolyDay_Gen));			//월차발생작업
	m_viewList.SetAt(ID_32789, RUNTIME_CLASS(Mon_Work_Edit_View));			//월근태내역 수정조회
	m_viewList.SetAt(ID_32790, RUNTIME_CLASS(Mon_Overwork_View));			//월근태잔업시간 조회
	m_viewList.SetAt(ID_32791, RUNTIME_CLASS(Mon_Attend_Print));			//월근태 회람자료 출력
	m_viewList.SetAt(ID_32792, RUNTIME_CLASS(Mon_Person_Attend_Print));			//개인별 월출근부 출력
	m_viewList.SetAt(ID_32793, RUNTIME_CLASS(Mon_Work_Print));			//월출근부 출력
	m_viewList.SetAt(ID_32794, RUNTIME_CLASS(Mon_Manager_Attend_View));			//부장/차장 월출근부
	m_viewList.SetAt(ID_32795, RUNTIME_CLASS(Mon_HolyDay_View));			//월별 월차내역 조회
	m_viewList.SetAt(ID_32796, RUNTIME_CLASS(Mon_Dep_Daily_Att));			//부서별 일구간 근태
	m_viewList.SetAt(ID_32797, RUNTIME_CLASS(Mon_HolyDay_Viewedit));			//월차조회/수정
	m_viewList.SetAt(ID_32798, RUNTIME_CLASS(Mon_HolyDay_Check));			//년월차확인
	
	//급여기초관리
	m_viewList.SetAt(ID_32801, RUNTIME_CLASS(Pay_Person_Monpay_Assign));			//개인별 월정급여 등록
	m_viewList.SetAt(ID_32802, RUNTIME_CLASS(Pay_Deduct_Extra_Assign));			//고정공제및 수당등록
	m_viewList.SetAt(ID_32803, RUNTIME_CLASS(Pay_Var_Deduct_Extra_Assign));			//가변공제및 수당등록
	m_viewList.SetAt(ID_32804, RUNTIME_CLASS(Pay_Workpay_List));			//근태관련 급여 리스트
	
	//기초코드관리
	
	m_viewList.SetAt(ID_32805, RUNTIME_CLASS(Code_Personpay_Assign));			//인사, 급여코드 등록
	m_viewList.SetAt(ID_32806, RUNTIME_CLASS(Code_Personpay_List));			//인사, 급여코드 리스트
	m_viewList.SetAt(ID_32807, RUNTIME_CLASS(Code_Company_Assign));			//회사기본내역 등록
	m_viewList.SetAt(ID_32808, RUNTIME_CLASS(Code_Postnum_Assign));			//우편번호부 등록
	
	
	//프로그램관리
	
	m_viewList.SetAt(ID_32810, RUNTIME_CLASS(Chulgeun_isang));			//개인별 패스워드 관리
	m_viewList.SetAt(ID_32811, RUNTIME_CLASS(Prog_dbmanage));			//데이터베이스 관리
}


BOOL CMainFrame::OnEraseMDIClientBackground(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	BITMAP bm;
	CDC dcMem;
	m_bitmap.GetObject(sizeof(BITMAP), (LPVOID)&bm);
	dcMem.CreateCompatibleDC(NULL);
	CBitmap *pOldBitmap = dcMem.SelectObject(&m_bitmap);

	for (int nX = 0; nX < rect.Width(); nX += bm.bmWidth)
		for (int nY = 0; nY < rect.Height(); nY += bm.bmHeight)
			pDC->BitBlt(nX, nY, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pOldBitmap);

	return TRUE;

	//return CMDIFrameWndEx::OnEraseBkgnd(pDC);
}
