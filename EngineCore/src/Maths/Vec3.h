#pragma once

namespace Math
{
	/**
	 * \brief Vector 3D Float class
	 */
	class Vec3
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
		 * \brief Copy vector
		 * \param _other_vector Vetor to copy
		 */
		void operator=(Vec3 _other_vector);
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
		 * \brief Substract vector
		 * \param _other_vec Vector to substract
		 * \return Vector result
		 */
		Vec3 operator-(Vec3 _other_vec) const;
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
