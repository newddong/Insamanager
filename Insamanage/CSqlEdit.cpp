// CSqlEdit.cpp: 구현 파일
//

#include "stdafx.h"
#include "Insamanage.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "InsamanageDoc.h"

#include "CSqlEdit.h"

#include "Prog_dbmanage.h"


// CSqlEdit

IMPLEMENT_DYNAMIC(CSqlEdit, CEdit)

CSqlEdit::CSqlEdit()
{

}

CSqlEdit::~CSqlEdit()
{
}


BEGIN_MESSAGE_MAP(CSqlEdit, CEdit)
	
END_MESSAGE_MAP()



// CSqlEdit 메시지 처리기







BOOL CSqlEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
						   			 		
			
			CString str;
			CMainFrame* pMfrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			CChildFrame* pCfrm = (CChildFrame*)pMfrm->GetActiveFrame();
			Prog_dbmanage* pView = (Prog_dbmanage*)pCfrm->GetActiveView();
			CInsamanageDoc* pDoc = (CInsamanageDoc*)pCfrm->GetActiveDocument();


			
			int len = this->LineLength(this->LineIndex());
			this->GetLine(0, str.GetBuffer(len), len);
			str.ReleaseBuffer(len);

						
			pView->m_dbList.DeleteAllItems();
			while (pView->m_dbList.DeleteColumn(0));
			UpdateData(TRUE);

						
			char* file = "Database.db";
			char* query = pDoc->StringToChar(str);
				
			
						
			LVCOLUMN Col;
			pDoc->DB_GetTable(file, query, pView->m_dbList, pView->m_arTxts, Col);
			//pDoc->DB_GetTable(file, sql, m_dbList);
			
		}


	}





	return CEdit::PreTranslateMessage(pMsg);
}
