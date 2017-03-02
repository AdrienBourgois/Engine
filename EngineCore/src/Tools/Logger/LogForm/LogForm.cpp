// LogForm.cpp : implementation file
//

#include "LogForm.h"
#include "afxdialogex.h"
#include "resource.h"


// LogForm dialog

IMPLEMENT_DYNAMIC(LogForm, CDialogEx)

LogForm::LogForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
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


// LogForm message handlers
