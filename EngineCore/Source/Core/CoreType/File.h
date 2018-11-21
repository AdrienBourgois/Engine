#pragma once

#include "Core/CoreType/String.h"

namespace Core
{
	namespace CoreType
	{
		class File
		{
		public:
			explicit File(const String& _path);
			~File();

		private:
			String path;

		};
	}
}
