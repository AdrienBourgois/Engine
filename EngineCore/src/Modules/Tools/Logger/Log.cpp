﻿#include "Modules/Tools/Logger/Log.h"

namespace Module
{
	namespace Tools
	{
		Log::Log(Core::CoreType::String _message, ELog_level _level) : message(_message), level(_level)
		{}
	}
}