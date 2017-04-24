#pragma once

#include "Engine.h"
#include "Core/Interface/IComponent.h"
#include "Objects/GameObject.h"
#include "Core/CoreType/Vertex.h"

namespace Object
{
	namespace Component
	{
		class GraphicComponent : public Core::Interface::IComponent
		{
		public:
			DECLARE_COMPONENT(S("GraphicComponent"), Core::CoreType::EObjectSubtype::GraphicComponent)

			explicit GraphicComponent(Core::CoreType::Vertex _points[], int _size);
			~GraphicComponent() = default;

			Core::CoreType::Vertex* GetPoints();
			int GetSize() const;
			Core::CoreType::Id GetId() const;

		private:
			std::vector<Core::CoreType::Vertex> vertexs;
			Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::GraphicComponent);
		};
	}
}

