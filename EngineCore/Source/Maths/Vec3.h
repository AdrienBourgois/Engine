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
	 * \brief Vector 3D Float
	 */
	class ENGINEDLL_API Vec3
	{
	public:
		/**
		 * \brief Default constructor
		 */
		Vec3() = default;
		/**
		 * \brief Constructor that initialize all components to same value
		 * \param _value Value used to initialize
		 */
		explicit Vec3(float _value);
		/**
		 * \brief Constructor to initialize all components
		 * \param _x x value
		 * \param _y y value
		 * \param _z z value
		 */
		Vec3(float _x, float _y, float _z);
		/**
		 * \brief Default copy constructor
		 * \param _other_vec Vector to copy
		 */
		Vec3(const Vec3& _other_vec) = default;

		/**
		 * \brief Copy members vector
		 * \param _other_vector Vector with members to copy
		 * \return Reference to vector
		 */
		Vec3& operator=(Vec3 _other_vector);
		/**
		 * \brief Set all members to same value
		 * \param _value Value to set for each member
		 * \return Reference to vector
		 */
		Vec3& operator=(float _value);
		/**
		 * \brief Compare vector
		 * \param _other_vec Vector to compare
		 * \return Comparison result
		 */
		bool operator==(Vec3 _other_vec) const;
		/**
		 * \brief Compare vector
		 * \param _other_vec Vector to compare
		 * \return Comparison result
		 */
		bool operator!=(Vec3 _other_vec) const;
		/**
		 * \brief Add vector
		 * \param _other_vec Vector to add
		 * \return Vector result
		 */
		Vec3 operator+(Vec3 _other_vec) const;
		/**
		 * \brief Add value to each member of vector
		 * \param _value Value to add
		 * \return Vector result
		 */
		Vec3 operator+(float _value) const;
		/**
		 * \brief Substract vector
		 * \param _other_vec Vector to substract
		 * \return Vector result
		 */
		Vec3 operator-(Vec3 _other_vec) const;
		/**
		 * \brief Substract value to each member of vector
		 * \param _value Value to substract
		 * \return Vector result
		 */
		Vec3 operator-(float _value) const;
		/**
		 * \brief Return the opposite vector
		 * \return Opposite vector
		 */
		Vec3 operator-() const;
		/**
		 * \brief Add vector to this vector
		 * \param _other_vec Vector to add
		 */
		void operator+=(Vec3 _other_vec);
		/**
		 * \brief Substract vector to this vector
		 * \param _other_vec Vector to substract
		 */
		void operator-=(Vec3 _other_vec);
		/**
		 * \brief Add value to this vector
		 * \param _value value to add
		 */
		void operator+=(float _value);
		/**
		 * \brief Substract value to this vector
		 * \param _value Value to substract
		 */
		void operator-=(float _value);
		/**
		 * \brief Is vector != 0
		 */
		explicit operator bool() const;

		/**
		 * \brief Return length of vector
		 * \return Length of vector
		 */
		float Length() const;
		/**
		 * \brief Normalize the vector
		 */
		void Normalize();
		/**
		 * \brief Return a normalized version of this vector
		 * \return Normalized vector
		 */
		Vec3 Normalized() const;
		/**
		 * \brief Dot product of vectors
		 * \param _other_vec Other vector to compute
		 * \return Scalar result
		 */
		float Dot(Vec3 _other_vec) const;
		/**
		 * \brief Cross product of vectors
		 * \param _other_vec Other vector to compute
		 * \return Result vector
		 */
		Vec3 Cross(Vec3 const _other_vec) const;

		/**
		 * \brief x component
		 */
		float x = 0;
		/**
		 * \brief y component
		 */
		float y = 0;
		/**
		 * \brief z component
		 */
		float z = 0;
	};
}
