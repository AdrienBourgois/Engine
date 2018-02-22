#pragma once

#include "Maths/Vec3.h"
#include "Core/CoreType/Color.h"

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief Store location and color data for vertex
		 */
		class ENGINEDLL_API Vertex
		{
		public:
			/**
			 * \brief Default constructor (Position 0/0/0 - Color white)
			 */
			Vertex() = default;
			/**
			 * \brief Constructor with 7 float
			 * \param _x Location x
			 * \param _y Location y
			 * \param _z Location z
			 * \param _r Color red
			 * \param _g Color green
			 * \param _b Color blue
			 * \param _a Color alpha
			 */
			Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a);
			/**
			 * \brief Constructor with location as float and Color as color
			 * \param _x Location x
			 * \param _y Location y
			 * \param _z Location z
			 * \param _color Color
			 */
			Vertex(float _x, float _y, float _z, Color _color);
			/**
			 * \brief Constructor with Vec3 as location and 4 float as color
			 * \param _location Location vector
			 * \param _r Color red
			 * \param _g Color green
			 * \param _b Color blue
			 * \param _a Color alpha
			 */
			Vertex(Math::Vec3 _location, float _r, float _g, float _b, float _a);
			/**
			 * \brief Constructor with location and color components
			 * \param _location Location vector
			 * \param _color Color
			 */
			Vertex(Math::Vec3 _location, Color _color);
			/**
			 * \brief Constructor with only location component (default color : white)
			 * \param _location Location vector
			 */
			explicit Vertex(Math::Vec3 _location);
			/**
			 * \brief Constructor with only color component (default location : 0/0/0)
			 * \param _color Color
			 */
			explicit Vertex(Color _color);

			/**
			 * \brief Set a new vector location for vertex
			 * \param _new_location Vector of new location
			 */
			void SetLocation(Math::Vec3 _new_location);
			/**
			 * \brief Set new color for vertex
			 * \param _new_color New color
			 */
			void SetColor(Color _new_color);

			/**
			 * \brief Return a pointer to array with data
			 * \return Array pointer
			 */
			const float* GetTable() const { return data; }

			/**
			 * \brief Return size of data
			 * \return Size of data in bytes
			 */
			static int GetSize() { return sizeof data; }

		private:
			/**
			 * \brief Array with data continue in memory
			 */
			float data[7] = {0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f};
		};
	}
}
