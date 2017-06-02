#pragma once

#include "Core/CoreType/Vertex.h"

namespace Core
{
	namespace CoreType
	{
		namespace PrimitiveMesh
		{
			enum class PrimitivesMeshType
			{
				Cube,
			};

			static const Vertex CubeVertices[] =
			{
				// front face
				{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

				// right side face
				{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

				// left side face
				{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

				// back face
				{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{ -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

				// top face
				{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

				// bottom face
				{  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
				{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },
				{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
				{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
			};

			static unsigned int CubeIndexs[] =
			{
				// front face
				0, 1, 2, // first triangle
				0, 3, 1, // second triangle

				// left face
				4, 5, 6, // first triangle
				4, 7, 5, // second triangle

				// right face
				8, 9, 10, // first triangle
				8, 11, 9, // second triangle

				// back face
				12, 13, 14, // first triangle
				12, 15, 13, // second triangle

				// top face
				16, 17, 18, // first triangle
				16, 19, 17, // second triangle

				// bottom face
				20, 21, 22, // first triangle
				20, 23, 21, // second triangle
			};
		}
	}
}