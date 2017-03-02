#include "LogForm.h"
#include "afxdialogex.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(LogForm, CDialogEx)

LogForm::LogForm(CWnd* pParent)	: CDialogEx(LOG_DIALOG, pParent)
{
}

LogForm::~LogForm()
{
}

void LogForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LogForm, CDialogEx)
END_MESSAGE_MAP()
