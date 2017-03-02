#pragma once

#include <afxdialogex.h>

class LogForm : public CDialogEx
{
	DECLARE_DYNAMIC(LogForm)

	explicit LogForm(CWnd* pParent = nullptr);
	virtual ~LogForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = LOG_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;

	DECLARE_MESSAGE_MAP()
};
