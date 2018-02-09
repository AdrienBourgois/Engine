#include "Vec3.h"
#include <cmath>

Math::Vec3::Vec3(float _value): x(_value), y(_value), z(_value)
{}

Math::Vec3::Vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{}

void Math::Vec3::operator=(Vec3 _other_vector)
{
	x = _other_vector.x;
	y = _other_vector.y;
	z = _other_vector.z;
}

bool Math::Vec3::operator==(Vec3 _other_vec) const
{
	if(x == _other_vec.x && y == _other_vec.y && z == _other_vec.z)
		return true;
	return false;
}

bool Math::Vec3::operator!=(Vec3 _other_vec) const
{
	return !operator==(_other_vec);
}

Math::Vec3 Math::Vec3::operator+(Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x + _other_vec.x;
	result_vec.y = y + _other_vec.y;
	result_vec.z = z + _other_vec.z;
	return result_vec;
}

Math::Vec3 Math::Vec3::operator+(float _value) const
{
	return Vec3(x + _value, y + _value, z + _value);
}

Math::Vec3 Math::Vec3::operator-(Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x - _other_vec.x;
	result_vec.y = y - _other_vec.y;
	result_vec.z = z - _other_vec.z;
	return result_vec;
}

Math::Vec3 Math::Vec3::operator-(float _value) const
{
	return Vec3(x - _value, y - _value, z - _value);
}

Math::Vec3 Math::Vec3::operator-() const
{
	return { -x, -y, -z };
}

void Math::Vec3::operator+=(Vec3 _other_vec)
{
	x += _other_vec.x;
	y += _other_vec.y;
	z += _other_vec.z;
}

void Math::Vec3::operator-=(Vec3 _other_vec)
{
	x -= _other_vec.x;
	y -= _other_vec.y;
	z -= _other_vec.z;
}

void Math::Vec3::operator+=(float _value)
{
	x += _value;
	y += _value;
	z += _value;
}

void Math::Vec3::operator-=(float _value)
{
	x -= _value;
	y -= _value;
	z -= _value;
}

Math::Vec3::operator bool() const
{
	if(x || y || z)
		return true;
	return false;
}

float Math::Vec3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

void Math::Vec3::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
}

Math::Vec3 Math::Vec3::Normalized() const
{
	Vec3 new_vector(x, y, z);
	float length = Length();
	new_vector.x /= length;
	new_vector.y /= length;
	new_vector.z /= length;
	return new_vector;
}

float Math::Vec3::Dot(Vec3 _other_vec) const
{
	return x*_other_vec.x + y*_other_vec.y + z*_other_vec.z;
}

Math::Vec3 Math::Vec3::Cross(Vec3 const _other_vec) const
{
	return{ (y * _other_vec.z - z * _other_vec.y), (z * _other_vec.x - x * _other_vec.z), (x * _other_vec.y - y * _other_vec.x) };
}
