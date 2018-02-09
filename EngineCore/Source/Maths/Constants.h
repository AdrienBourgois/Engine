#pragma once

namespace Math
{
	/**
	 * \brief Pi value
	 */
	const float Pi = 3.141592653589793f;

	/**
	 * \brief Convert Degree angle to Radian
	 * \param _angle Angle to convert
	 * \return Angle in Radian
	 */
	inline float Deg2Rad(float _angle)
	{
		return _angle * Pi / 180.f;
	}

	/**
	 * \brief Convert Radian angle to Degree
	 * \param _angle Angle to convert
	 * \return Angle in Degree
	 */
	inline float Rad2Deg(float _angle)
	{
		return _angle * 180.f / Pi;
	}
}