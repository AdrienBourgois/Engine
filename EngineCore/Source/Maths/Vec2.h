#pragma once

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
	 * \brief Vector 2D Float
	 */
	class ENGINEDLL_API Vec2
	{
	public:
		/**
		 * \brief Default constructor
		 */
		Vec2() = default;
		/**
		 * \brief Constructor that initialize all components to same value
		 * \param _value Value used to initialize
		 */
		explicit Vec2(float _value);
		/**
		 * \brief Constructor to initialize all components
		 * \param _x x value
		 * \param _y y value
		 */
		Vec2(float _x, float _y);
		/**
		 * \brief Default copy constructor
		 * \param _other_vec Vector to copy
		 */
		Vec2(const Vec2& _other_vec) = default;

		/**
		 * \brief Copy vector
		 * \param _other_vec Vector to copy
		 */
		Vec2& operator=(Vec2 _other_vec);
		/**
		 * \brief Set all members to same value
		 * \param _value Value to set for each member
		 * \return Reference to this vector
		 */
		Vec2& operator=(float _value);

		/**
		 * \brief Compare vector
		 * \param _other_vec Vector to compare
		 * \return Comparison result
		 */
		bool operator==(Vec2 _other_vec) const;
		/**
		 * \brief Compare vector
		 * \param _other_vec Vector to compare
		 * \return Comparison result
		 */
		bool operator!=(Vec2 _other_vec) const;
		/**
		 * \brief Is vector != (0,0)
		 */
		explicit operator bool() const;

		/**
		 * \brief Add vector
		 * \param _other_vec Vector to add
		 * \return Vector result
		 */
		Vec2 operator+(Vec2 _other_vec) const;
		/**
		 * \brief Subtract vector
		 * \param _other_vec Vector to subtract
		 * \return Vector result
		 */
		Vec2 operator-(Vec2 _other_vec) const;
		/**
		 * \brief Add vector to this vector
		 * \param _other_vec Vector to add
		 */
		void operator+=(Vec2 _other_vec);
		/**
		 * \brief Subtract vector to this vector
		 * \param _other_vec Vector to subtract
		 */
		void operator-=(Vec2 _other_vec);

		/**
		 * \brief Add value to each member of vector
		 * \param _value Value to add
		 * \return Vector result
		 */
		Vec2 operator+(float _value) const;
		/**
		 * \brief Subtract value to each member of vector
		 * \param _value Value to subtract
		 * \return Vector result
		 */
		Vec2 operator-(float _value) const;
		/**
		 * \brief Multiply value to each member of vector
		 * \param _value Value to multiply
		 * \return Vector result
		 */
		Vec2 operator*(float _value) const;
		/**
		 * \brief Divide value to each member of vector
		 * \param _value Value with which divide
		 * \return Vector result
		 */
		Vec2 operator/(float _value) const;

		/**
		 * \brief Add value to this vector
		 * \param _value Value to add
		 * \return Reference to this vector
		 */
		Vec2& operator+=(float _value);
		/**
		 * \brief Subtract value to this vector
		 * \param _value Value to subtract
		 * \return Reference to this vector
		 */
		Vec2& operator-=(float _value);
		/**
		 * \brief Multiply value to this vector
		 * \param _value Value to multiply
		 * \return Reference to this vector
		 */
		Vec2& operator*=(float _value);
		/**
		 * \brief Divide value to this vector
		 * \param _value Value with which divide
		 * \return Reference to this vector
		 */
		Vec2& operator/=(float _value);

		/**
		 * \brief Return the opposite vector
		 * \return Opposite vector
		 */
		Vec2 operator-() const;

		/**
		 * \brief Return length of vector
		 * \return Length of vector
		 */
		float Length() const;
		/**
		 * \brief Normalize the vector
		 */
		Vec2& Normalize();
		/**
		 * \brief Return a normalized version of this vector
		 * \return Normalized vector
		 */
		Vec2 Normalized() const;
		/**
		 * \brief Dot product of vectors
		 * \param _other_vec Other vector to compute
		 * \return Scalar result
		 */
		float Dot(Vec2 _other_vec) const;

		/**
		 * \brief Compute angle in radian between this vector and another vector
		 * \param _other_vec Other vector to compute
		 * \return Angle in radian
		 */
		float Angle(Vec2 _other_vec) const;

		/**
		 * \brief x component
		 */
		float x = 0;
		/**
		 * \brief y component
		 */
		float y = 0;
	};
}
