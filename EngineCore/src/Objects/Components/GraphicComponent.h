#pragma once

#include "Core/Interface/IComponent.h"
#include "Core/CoreType/Vertex.h"
#include "Core/CoreType/Transform.h"

namespace Object
{
	namespace Component
	{
		/**
		 * \brief Component to handle graphics objects (vertices, indexs, ...)
		 */
		class ENGINEDLL_API GraphicComponent : public Core::Interface::IComponent
		{
		public:
			DECLARE_COMPONENT(S("GraphicComponent"), Core::CoreType::EObjectSubtype::GraphicComponent)

			/**
			 * \brief Contructor
			 * \param _vertexs_array Array of vertices
			 * \param _vertexs_count Count of vertex in array / Array size
			 * \param _indexs_array Array of indexs (if index buffer needed)
			 * \param _indexs_count Count of indexs in array / Array size (if index buffer needed)
			 */
			explicit GraphicComponent(Core::CoreType::Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[] = {}, unsigned int _indexs_count = 0);
			/**
			 * \brief Default destructor
			 */
			~GraphicComponent() = default;

			/**
			 * \brief Specify if vertices are indexed or not
			 * \return Is component indexed
			 */
			bool IsIndexed() const;

			Core::CoreType::Transform GetTransform() const;
			Core::CoreType::Transform* GetTransformReference() const;

			/**
			 * \brief Return an array with vertices
			 * \return Array of vertices
			 */
			Core::CoreType::Vertex* GetVertices() const;
			/**
			 * \brief Return an array with indexs
			 * \return Array of indexs
			 */
			unsigned int* GetIndexs() const;
			/**
			 * \brief Return the number of vertices
			 * \return Count of vertices
			 */
			int GetVertexCount() const;
			/**
			 * \brief Return the number of indexs
			 * \return Count of indexs
			 */
			int GetIndexCount() const;

			/**
			 * \brief Return the Id of component
			 * \return Id of component
			 */
			Core::CoreType::Id GetId() const;

		private:
			bool indexed = false;

			std::vector<Core::CoreType::Vertex>* vertices = new std::vector<Core::CoreType::Vertex>();
			std::vector<unsigned int>* indexs = new std::vector<unsigned>();
			Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::GraphicComponent);
		};
	}
}

