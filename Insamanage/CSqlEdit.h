#pragma once


// CSqlEdit

class CSqlEdit : public CEdit
{
	DECLARE_DYNAMIC(CSqlEdit)

public:
	CSqlEdit();
	virtual ~CSqlEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


