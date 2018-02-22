#include "Modules/Tools/Logs/Log.h"
#include "Modules/Time/Clock.h"

namespace Module
{
	namespace Tools
	{
		Logs::Log::Log(const Core::CoreType::String& _message, const ELog_level _level) : message(_message), level(_level)
		{
			time = Time::Clock::Now();
		}

		Logs::Log::Log(const Core::CoreType::String& _message, const ELog_level _level, const Core::CoreType::String& _file, const int _line) : message(_message), level(_level), file(_file), line(_line)
		{
			time = Time::Clock::Now();
		}

		Core::CoreType::String Logs::Log::GetStructuredLog()
		{
			if(structuredLog.IsEmpty())
			{
				structuredLog.Reserve(50);
				structuredLog += S("\t(") + time.ToString() + S(") ");
				if(!file.IsNull())
					structuredLog += file + ':' + SN(line);
				structuredLog += '\n';
				structuredLog += message;
			}

			return structuredLog;
		}
	}
}
