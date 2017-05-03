#pragma once

#include "Macros.h"

namespace Core {
	namespace CoreType {
		class Vertex;
	}
}

namespace Object {
	namespace Component {
		class GraphicComponent;
	}
}

namespace Core
{
	namespace Interface
	{
		/**
		 * \brief Interface for Render API implementation
		 */
		class IRender
		{
		public:
			/**
			 * \brief Default virtual destructor
			 */
			virtual ~IRender() = default;

			/**
			 * \brief Initialize renderer (configuration, ...)
			 * \return Is function success
			 */
			virtual bool Initialize() = 0;
			/**
			 * \brief Create and initialize pipeline
			 * \return Is function success
			 */
			virtual bool CreatePipeline() = 0;
			/**
			 * \brief Create a buffer from object
			 * \param _id Id of object
			 * \param _vertex Array of vertexs
			 * \param _size Size of array
			 * \param _name Name of buffer
			 * \return Is function success
			 */
			virtual bool CreateVertexBuffer(int _id, const CoreType::Vertex* _vertex, int _size, CoreType::String _name) = 0;
			/**
			 * \brief Start render of current frame
			 * \return Is function success
			 */
			virtual bool Render() = 0;
			/**
			 * \brief Stop API and destruct all components
			 * \return Is function success
			 */
			virtual bool Cleanup() = 0;
		};
	}
}
