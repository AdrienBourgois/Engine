#pragma once

#include <afxdialogex.h>

// LogForm dialog

class LogForm : public CDialogEx
{
	DECLARE_DYNAMIC(LogForm)

public:
	explicit LogForm(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LogForm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = LOG_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnQuitButtonClicked();
};
