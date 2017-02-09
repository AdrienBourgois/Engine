#include "Tools/Logger/LogForm/LogFormHandle.h"

namespace Tools
{
	LogFormHandle::LogFormHandle()
	{
	}

	LogFormHandle::~LogFormHandle()
	{
	}

	void LogFormHandle::DisplayDialog()
	{
		CreateDlg(L"LOG_DIALOG", nullptr);
	}

	void LogFormHandle::QuitDialog()
	{
		EndDialog(0);
	}
}
