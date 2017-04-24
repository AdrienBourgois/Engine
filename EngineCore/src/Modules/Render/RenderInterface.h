#pragma once

#include "Engine.h"
#include "Core/Interface/IModule.h"
#include "Core/Interface/IRender.h"
#include "Objects/Components/GraphicComponent.h"

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
			DECLARE_MODULE(S("Render Interface"))

			bool CreateBuffer(Object::Component::GraphicComponent* _object);

		private:
			RenderAPI api = DirectX12Api;
			Core::Interface::IRender* renderer = nullptr;

			std::unordered_map<int, Object::Component::GraphicComponent*> objects;
		};
	}
}
