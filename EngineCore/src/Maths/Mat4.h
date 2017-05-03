#pragma once

#include "Vec3.h"

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

namespace Math
{
	/**
	 * \brief Matrix 4 X 4
	 */
	class ENGINEDLL_API Mat4
	{
	public:
		/**
		 * \brief Constructor (initialize all Values to 0, use Mat4::Identity to get identity matrix)
		 */
		Mat4();
		/**
		 * \brief Constructor (by constructor parameters)
		 * \param _1 Value 1	\param _2 Value 2	\param _3 Value 3	\param _4 Value 4
		 * \param _5 Value 5	\param _6 Value 6	\param _7 Value 7	\param _8 Value 8
		 * \param _9 Value 9	\param _10 Value 10 \param _11 Value 11	\param _12 Value 12
		 * \param _13 Value 13	\param _14 Value 14 \param _15 Value 15	\param _16 Value 16
		 */
		Mat4(float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15, float _16);
		/**
		 * \brief Constructor (by array)
		 * \param _values Array of Values
		 */
		explicit Mat4(float _values[16]);

		/**
		 * \brief Values storage array
		 */
		float Values[16];

		/**
		 * \brief Constant identity matrix
		 */
		static Mat4 const Identity;

		/**
		 * \brief Create a translation matrix
		 * \param _x x value
		 * \param _y y value
		 * \param _z z value
		 * \return Translation matrix
		 */
		static Mat4 Translate(float _x, float _y, float _z);
		/**
		 * \brief Create a translation matrix
		 * \param _translation Translation vector
		 * \return Translation matrix
		 */
		static Mat4 Translate(Vec3 _translation);

		/**
		 * \brief Create a scale matrix
		 * \param _x x value
		 * \param _y y value
		 * \param _z z value
		 * \return Scale matrix
		 */
		static Mat4 Scale(float _x, float _y, float _z);
		/**
		 * \brief Create a scale matrix
		 * \param _scale Scale vector
		 * \return Scale matrix
		 */
		static Mat4 Scale(Vec3 _scale);
		/**
		 * \brief Create a scale matrix
		 * \param _scale Scale scalar
		 * \return Scale matrix
		 */
		static Mat4 Scale(float _scale);

		/**
		 * \brief Create a rotation matrix on x axis
		 * \param _angle Angle in degree
		 * \return Rotation matrix
		 */
		static Mat4 RotateX(float _angle);
		/**
		 * \brief Create a rotation matrix on y axis
		 * \param _angle Angle in degree
		 * \return Rotation matrix
		 */
		static Mat4 RotateY(float _angle);
		/**
		 * \brief Create a rotation matrix on z axis
		 * \param _angle Angle in degree
		 * \return Rotation matrix
		 */
		static Mat4 RotateZ(float _angle);
		/**
		 * \brief Create a rotation matrix
		 * \param _rotation Rotation vector
		 * \return Rotation matrix
		 */
		static Mat4 Rotate(Vec3 _rotation);

		/**
		 * \brief Access to Values
		 * \param _element Value number
		 * \return Reference to value
		 */
		float& operator[](int _element);
		/**
		 * \brief Verify if two matrix are identicals
		 * \param _other Other matrix to compare
		 * \return Are matrix idendicals
		 */
		bool operator==(Mat4 _other) const;
		/**
		 * \brief Verify if two matrix are differents
		 * \param _other Other matrix to compare
		 * \return Are matrix differents
		 */
		bool operator!=(Mat4 _other) const;
		/**
		 * \brief Multiply two matrices
		 * \param _matrix Other matrix to multiply
		 * \return Result matrix
		 */
		Mat4 operator*(Mat4 const& _matrix) const;
		/**
		 * \brief Multiply this matrix with another matrix
		 * \param _matrix Other matrix to multiply
		 */
		void operator*=(Mat4 const& _matrix);

		/**
		 * \brief Verify if matrix is orthogonal
		 * \return Is matrix orthogonal
		 */
		bool IsOrthogonal();
		/**
		 * \brief Get the inverse of the matrix
		 * \return Inverse matrix
		 */
		Mat4 GetInverse() const;
		/**
		 * \brief Get the transpose of the matrix
		 * \return Transpose matrix
		 */
		Mat4 GetTranspose() const;

		/*void SetPosition(Vec3 _vec);
		Vec3 GetPosition() const;

		void SetRotation(Vec3 _rotation);
		Vec3 GetRotation() const;

		void SetScale(Vec3 _scale);
		Vec3 GetScale() const;*/
	};
}
