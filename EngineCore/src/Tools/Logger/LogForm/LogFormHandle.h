#pragma once

#include "engine.h"
#include "Tools/Logger/LogForm/LogForm.h"

namespace Tools
{
	class ENGINEDLL_API LogFormHandle : public LogForm
	{
		DECLARE_DYNAMIC(LogFormHandle)

	public:
		LogFormHandle();
		~LogFormHandle();

		void RegisterDialog() const;
		void DisplayDialog();
		void QuitDialog();
	};
}
