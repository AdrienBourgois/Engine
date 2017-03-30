#pragma once

#include "Engine.h"
#include "Core/Interface/IModule.h"
#include "Core/Interface/IRender.h"

namespace Module
{
	namespace Render
	{
		enum RenderAPI
		{
			DirectX12Api,
		};

		class RenderInterface : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Render Interface"));

		private:
			RenderAPI api = DirectX12Api;
			Core::Interface::IRender* renderer = nullptr;
		};
	}
}
