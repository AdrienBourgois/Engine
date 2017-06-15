#include "Modules/Tools/Logs/Log.h"

namespace Module
{
	namespace Tools
	{
		Logs::Log::Log(Core::CoreType::String _message, ELog_level _level) : message(_message), level(_level)
		{}
	}
}
