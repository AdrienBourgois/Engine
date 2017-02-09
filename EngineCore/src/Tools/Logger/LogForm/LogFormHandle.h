#pragma once

#include "Tools/Logger/LogForm/LogForm.h"

namespace Tools
{
	class LogFormHandle : public LogForm
	{
	public:
		LogFormHandle();
		~LogFormHandle();

		void DisplayDialog();
		void QuitDialog();

		afx_msg void OnQuitButtonClicked() override { QuitDialog(); }
	};
}
