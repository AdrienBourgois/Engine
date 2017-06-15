#pragma once
#include "Script.h"
#include "Objects/GameObject.h"

namespace Scripts
{
	/**
	 * \brief Script with GameObject attached to
	 */
	class ENGINEDLL_API GameObjectScript : public Script
	{
	public:
		/**
		 * \brief Constructor
		 */
		GameObjectScript();
		/**
		 * \brief Default destructor
		 */
		~GameObjectScript() = default;

	protected:
		/**
		 * \brief Create a mesh for attached game object
		 * \param _mesh Mesh type
		 */
		void MakeMesh(PrimitiveMesh::PrimitivesMeshType _mesh);

		/**
		 * \brief GameObject attached to this script
		 */
		Object::GameObject object = Object::GameObject(GetScriptName() + S(" GameObject"));
	};
}

