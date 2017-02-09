#pragma once

#define _WIN32_WINNT 0x0602

#include "resource.h"
#include "Tools/Logger/LogForm/LogForm.h"

// LogForm dialog

IMPLEMENT_DYNAMIC(LogForm, CDialogEx)

LogForm::LogForm(CWnd* pParent)	: CDialogEx(LOG_DIALOG, pParent)
{}

LogForm::~LogForm()
{}

void LogForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LogForm, CDialogEx)
	ON_BN_CLICKED(IDCLOSE, &LogForm::OnQuitButtonClicked)
END_MESSAGE_MAP()

// LogForm message handlers


void LogForm::OnQuitButtonClicked()
{
	EndDialog(0);
}
