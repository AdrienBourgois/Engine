#pragma once

#include "Engine.h"
#include "Core/Interface/IModule.h"
#include "Core/Interface/IRender.h"
#include "Objects/Components/GraphicComponent.h"
#include "Camera.h"

namespace Module
{
	/**
	 * \brief All render stuff (Interfaces, API, Wrappers, ...)
	 */
	namespace Render
	{
		/**
		 * \brief List of render API
		 */
		enum RenderAPI
		{
			DirectX12Api,
		};

		/**
		 * \brief Interface for rendering
		 */
		class ENGINEDLL_API RenderInterface : public Core::Interface::IModule
		{
		public:
			DECLARE_MODULE(S("Render Interface"))

			/**
			 * \brief Send an object to the renderer
			 * \param _component Graphic component to send to the renderer
			 * \return Is buffer created
			 */
			bool CreateBuffer(Object::Component::GraphicComponent* _component) const;

			/**
			 * \brief Return a pointer to the current active camera
			 * \return Current active camera
			 */
			Camera* GetActiveCamera() const;
		private:
			/**
			 * \brief Current render API used
			 */
			RenderAPI api = DirectX12Api;
			/**
			 * \brief Pointer to the renderer
			 */
			Core::Interface::IRender* renderer = nullptr;

			/**
			 * \brief Store list of object send to renderer, with the id
			 */
			std::unordered_map<unsigned int, Object::Component::GraphicComponent*>* objects = new std::unordered_map<unsigned, Object::Component::GraphicComponent*>();

			/**
			 * \brief Current active camera
			 */
			Camera* activeCamera = new Camera();
		};
	}
}
