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
		 * \brief GameObject attached to this script
		 */
		Object::GameObject object = Object::GameObject(GetScriptName() + S(" GameObject"));
	};
}

