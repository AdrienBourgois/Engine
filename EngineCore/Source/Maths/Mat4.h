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
		 * \brief Default constructor
		 */
		Mat4() = default;
		/**
		 * \brief Constructor (by constructor parameters)
		 * \param _0 Value 0	\param _1 Value 1	\param _2 Value 2	\param _3 Value 3
		 * \param _4 Value 4	\param _5 Value 5	\param _6 Value 6	\param _7 Value 7
		 * \param _8 Value 8	\param _9 Value 9	\param _10 Value 10 \param _11 Value 11
		 * \param _12 Value 12	\param _13 Value 13	\param _14 Value 14 \param _15 Value 15
		 */
		Mat4(float _0, float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15);
		/**
		 * \brief Constructor (by array)
		 * \param _values Array of values
		 */
		explicit Mat4(const float _values[16]);
		/**
		 * \brief Default copy constructor
		 * \param _other_mat Matrix to copy
		 */
		Mat4(const Mat4& _other_mat) = default;

		/**
		 * \brief Copy vector
		 * \param _other_mat Matrix to copy
		 */
		Mat4& operator=(Mat4 const& _other_mat);
		/**
		 * \brief Set all members to same value
		 * \param _value Value to set for each member
		 * \return Reference to this vector
		 */
		Mat4& operator=(float _value);

		/**
		 * \brief Constant identity matrix
		 */
		static Mat4 const Identity;

		/**
		 * \brief Access to Values
		 * \param _element Value number
		 * \return Reference to value
		 */
		float& operator[](int _element);

		/**
		 * \brief Verify if two matrix are identicals
		 * \param _other_mat Other matrix to compare
		 * \return Are matrix identicals
		 */
		bool operator==(Mat4 const& _other_mat) const;
		/**
		 * \brief Verify if two matrix are different
		 * \param _other_mat Other matrix to compare
		 * \return Are matrix different
		 */
		bool operator!=(Mat4 _other_mat) const;
		/**
		 * \brief Are all values of this matrix != 0
		 */
		explicit operator bool() const;

		/**
		 * \brief Add two matrices
		 * \param _other_mat Other matrix to add
		 * \return Result matrix
		 */
		Mat4 operator+(Mat4 const& _other_mat) const;
		/**
		 * \brief Subtract two matrices
		 * \param _other_mat Other matrix to subtract
		 * \return Result matrix
		 */
		Mat4 operator-(Mat4 const& _other_mat) const;
		/**
		 * \brief Multiply two matrices
		 * \param _other_mat Other matrix to multiply
		 * \return Result matrix
		 */
		Mat4 operator*(Mat4 const& _other_mat) const;
		/**
		 * \brief Add another matrix to this matrix
		 * \param _other_mat Other matrix to add
		 */
		Mat4& operator+=(Mat4 const& _other_mat);
		/**
		 * \brief Subtract another matrix to this matrix
		 * \param _other_mat Other matrix to subtract
		 */
		Mat4& operator-=(Mat4 const& _other_mat);
		/**
		 * \brief Multiply this matrix with another matrix
		 * \param _other_mat Other matrix to multiply
		 */
		Mat4& operator*=(Mat4 const& _other_mat);

		/**
		 * \brief Add scalar to each matrix values
		 * \param _value Value to add
		 * \return Result matrix
		 */
		Mat4 operator+(float _value) const;
		/**
		 * \brief Subtract scalar to each matrix values
		 * \param _value Value to subtract
		 * \return Result matrix
		 */
		Mat4 operator-(float _value) const;
		/**
		 * \brief Multiply matrix by a scalar
		 * \param _value Value to multiply
		 * \return Result matrix
		 */
		Mat4 operator*(float _value) const;
		/**
		 * \brief Divide matrix by a scalar
		 * \param _value Value with which divide
		 * \return Result matrix
		 */
		Mat4 operator/(float _value) const;
		/**
		 * \brief Add value to each values of this matrix
		 * \param _value Value to add
		 */
		Mat4& operator+=(float _value);
		/**
		 * \brief Subtract value to each values of this matrix
		 * \param _value Value to subtract
		 */
		Mat4& operator-=(float _value);
		/**
		 * \brief Multiply this matrix by a scalar
		 * \param _value Value to multiply
		 */
		Mat4& operator*=(float _value);
		/**
		 * \brief Divide this matrix by a scalar
		 * \param _value Value with which divide
		 */
		Mat4& operator/=(float _value);

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
		 * \brief Verify if matrix is orthogonal
		 * \return Is matrix orthogonal
		 */
		bool IsOrthogonal() const;
		/**
		 * \brief Get the inverse of the matrix
		 * \return Inverse matrix
		 */
		Mat4 GetInverse() const;
		/**
		 * \brief Transpose this matrix
		 * \return Reference to this matrix
		 */
		Mat4& Transpose();
		/**
		 * \brief Get the transpose of the matrix
		 * \return Transpose matrix
		 */
		Mat4 GetTranspose() const;

		/**
		 * \brief Create a perspective matrix
		 * \param _angle_of_view FOV in degree
		 * \param _aspect_ratio Aspect ratio of render
		 * \param _near Near limit of render
		 * \param _far Far limit of render
		 * \return Perspective projection matrix
		 */
		static Mat4 PerspectiveMatrix(float _angle_of_view, float _aspect_ratio, float _near, float _far);
		/**
		 * \brief Create a look at matrix
		 * \param _eye Position of the eye
		 * \param _target Position of target
		 * \param _up Up vector
		 * \return Look at matrix
		 */
		static Mat4 LookAt(Vec3 _eye, Vec3 _target, Vec3 _up);

		/**
		 * \brief Values storage array
		 */
		float values[16] {};
	};
}
