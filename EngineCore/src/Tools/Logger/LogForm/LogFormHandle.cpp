#include "Tools/Logger/LogForm/LogFormHandle.h"
#include "afxdialogex.h"
#include "resource.h"

namespace Tools
{
	IMPLEMENT_DYNAMIC(LogFormHandle, CDialogEx)

	LogFormHandle::LogFormHandle()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		AfxSetResourceHandle(AfxGetStaticModuleState()->m_hCurrentResourceHandle);
	}

	LogFormHandle::~LogFormHandle()
	{
	}

	INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			if (MessageBox(hDlg, TEXT("Close the window?"), TEXT("Close"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				DestroyWindow(hDlg);
			}
			return true;
		case WM_DESTROY:
			//PostQuitMessage(0);
			return true;

		default:
			return true;
		}
	}

	void LogFormHandle::RegisterDialog() const
	{
		if (!AfxWinInit(AfxGetStaticModuleState()->m_hCurrentResourceHandle, nullptr, ::GetCommandLine(), 0))
		{
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		}
	}

	void LogFormHandle::DisplayDialog()
	{
		/*AFX_MANAGE_STATE(AfxGetStaticModuleState());
		AfxSetResourceHandle(AfxGetStaticModuleState()->m_hCurrentResourceHandle);*/

		//CreateDialog(nullptr, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, DialogProc);
		//Create(MAKEINTRESOURCEW(IDD_DIALOG1));
		DoModal();
	}

	void LogFormHandle::QuitDialog()
	{
		DestroyWindow();
	}
}
