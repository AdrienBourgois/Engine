#pragma once

#include <afxdialogex.h>

// LogForm dialog

class LogForm : public CDialogEx
{
	DECLARE_DYNAMIC(LogForm)

public:
	LogForm(CWnd* pParent = NULL);   // standard constructor
	virtual ~LogForm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
