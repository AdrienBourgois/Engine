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
			 * \brief Create buffers from object
			 * \param _id Id of object
			 * \param _name Name of buffer
			 * \param _vertices_array Array of vertices
			 * \param _vertices_count Size of vertices array
			 * \param _indexs_array Array of indexs (If vertices are indexed)
			 * \param _indexs_count Size of indexs array
			 * \return Is function success
			 */
			virtual bool CreateBuffers(unsigned int _id, CoreType::String _name, CoreType::Vertex* _vertices_array, unsigned int _vertices_count, unsigned int* _indexs_array = nullptr, unsigned int _indexs_count = 0) = 0;
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