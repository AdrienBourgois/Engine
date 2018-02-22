#include "Vec3.h"
#include <cmath>

Math::Vec3::Vec3(const float _value): x(_value), y(_value), z(_value)
{}

Math::Vec3::Vec3(const float _x, const float _y, const float _z): x(_x), y(_y), z(_z)
{}

Math::Vec3& Math::Vec3::operator=(const Vec3 _other_vector)
{
	x = _other_vector.x;
	y = _other_vector.y;
	z = _other_vector.z;
	return *this;
}

Math::Vec3& Math::Vec3::operator=(const float _value)
{
	x = _value;
	y = _value;
	z = _value;
	return *this;
}

bool Math::Vec3::operator==(const Vec3 _other_vec) const
{
	return x == _other_vec.x && y == _other_vec.y && z == _other_vec.z;
}

bool Math::Vec3::operator!=(const Vec3 _other_vec) const
{
	return !operator==(_other_vec);
}

Math::Vec3 Math::Vec3::operator+(const Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x + _other_vec.x;
	result_vec.y = y + _other_vec.y;
	result_vec.z = z + _other_vec.z;
	return result_vec;
}

Math::Vec3 Math::Vec3::operator+(const float _value) const
{
	return Vec3(x + _value, y + _value, z + _value);
}

Math::Vec3 Math::Vec3::operator-(const Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x - _other_vec.x;
	result_vec.y = y - _other_vec.y;
	result_vec.z = z - _other_vec.z;
	return result_vec;
}

Math::Vec3 Math::Vec3::operator-(const float _value) const
{
	return Vec3(x - _value, y - _value, z - _value);
}

Math::Vec3 Math::Vec3::operator-() const
{
	return { -x, -y, -z };
}

void Math::Vec3::operator+=(const Vec3 _other_vec)
{
	x += _other_vec.x;
	y += _other_vec.y;
	z += _other_vec.z;
}

void Math::Vec3::operator-=(const Vec3 _other_vec)
{
	x -= _other_vec.x;
	y -= _other_vec.y;
	z -= _other_vec.z;
}

void Math::Vec3::operator+=(const float _value)
{
	x += _value;
	y += _value;
	z += _value;
}

void Math::Vec3::operator-=(const float _value)
{
	x -= _value;
	y -= _value;
	z -= _value;
}

Math::Vec3::operator bool() const
{
	return x || y || z;
}

float Math::Vec3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

void Math::Vec3::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
	z /= length;
}

Math::Vec3 Math::Vec3::Normalized() const
{
	Vec3 new_vector(x, y, z);
	const float length = Length();
	new_vector.x /= length;
	new_vector.y /= length;
	new_vector.z /= length;
	return new_vector;
}

float Math::Vec3::Dot(const Vec3 _other_vec) const
{
	return x*_other_vec.x + y*_other_vec.y + z*_other_vec.z;
}

Math::Vec3 Math::Vec3::Cross(Vec3 const _other_vec) const
{
	return{ (y * _other_vec.z - z * _other_vec.y), (z * _other_vec.x - x * _other_vec.z), (x * _other_vec.y - y * _other_vec.x) };
}
