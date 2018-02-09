#pragma once

#include "Core/Interface/IComponent.h"
#include "Core/CoreType/Vertex.h"
#include "Core/CoreType/Transform.h"
#include "Core/CoreType/Mesh.h"

namespace Object
{
	/**
	 * \brief Components for GameObject
	 */
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
			 * \brief Contructor with Mesh constructor
			 * \param _vertexs_array Array of vertices
			 * \param _vertexs_count Count of vertex in array / Array size
			 * \param _indexs_array Array of indexs (if index buffer needed)
			 * \param _indexs_count Count of indexs in array / Array size (if index buffer needed)
			 */
			explicit GraphicComponent(Core::CoreType::Vertex _vertexs_array[], unsigned int _vertexs_count, unsigned int _indexs_array[] = {}, unsigned int _indexs_count = 0);
			/**
			 * \brief Contructor from primitive mesh type
			 * \param _mesh_type Type of the primitive mesh
			 */
			explicit GraphicComponent(Core::CoreType::PrimitiveMesh::PrimitivesMeshType _mesh_type);
			/**
			 * \brief Constructor form existent mesh
			 * \param _mesh Mesh to use
			 */
			explicit GraphicComponent(Core::CoreType::Mesh _mesh);
			/**
			 * \brief Default destructor
			 */
			~GraphicComponent() = default;

			/**
			 * \brief Return the Transform of object
			 * \return Transform of object
			 */
			Core::CoreType::Transform GetTransform() const;
			/**
			 * \brief Return a pointer to the Transform kept by the class
			 * \return Reference to the Transform
			 */
			Core::CoreType::Transform* GetTransformReference() const;

			/**
			 * \brief Return Meshs
			 * \return Mesh
			 */
			Core::CoreType::Mesh* GetMesh() const;

			/**
			 * \brief Return the Id of component
			 * \return Id of component
			 */
			Core::CoreType::Id GetId() const;

		private:
			/**
			 * \brief Pointer to mesh
			 */
			Core::CoreType::Mesh* mesh = nullptr;
			/**
			 * \brief Store id of component
			 */
			Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::GraphicComponent);
		};
	}
}

