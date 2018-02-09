#include "Modules/Tools/Logs/Log.h"
#include "Modules/Time/Clock.h"

namespace Module
{
	namespace Tools
	{
		Logs::Log::Log(const Core::CoreType::String _message, const ELog_level _level) : message(_message), level(_level)
		{
			time = Time::Clock::Now();
		}

		Core::CoreType::String Logs::Log::GetStructuredLog()
		{
			if(structuredLog.IsEmpty())
			{
				structuredLog.Reserve(50);
				structuredLog += time.ToString() + S(" - ") + message;
			}

			return structuredLog;
		}
	}
}
