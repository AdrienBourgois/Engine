﻿#include "Vec3.h"
#include <cmath>

Math::Vec3::Vec3(const float _value): x(_value), y(_value), z(_value) {}

Math::Vec3::Vec3(const float _x, const float _y, const float _z): x(_x), y(_y), z(_z) {}

Math::Vec3& Math::Vec3::operator=(const Vec3 _other_vec)
{
	x = _other_vec.x;
	y = _other_vec.y;
	z = _other_vec.z;
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

Math::Vec3::operator bool() const
{
	return x || y || z;
}

Math::Vec3 Math::Vec3::operator+(const Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x + _other_vec.x;
	result_vec.y = y + _other_vec.y;
	result_vec.z = z + _other_vec.z;
	return result_vec;
}

Math::Vec3 Math::Vec3::operator-(const Vec3 _other_vec) const
{
	Vec3 result_vec;
	result_vec.x = x - _other_vec.x;
	result_vec.y = y - _other_vec.y;
	result_vec.z = z - _other_vec.z;
	return result_vec;
}

Math::Vec3& Math::Vec3::operator+=(const Vec3 _other_vec)
{
	x += _other_vec.x;
	y += _other_vec.y;
	z += _other_vec.z;
	return *this;
}

Math::Vec3& Math::Vec3::operator-=(const Vec3 _other_vec)
{
	x -= _other_vec.x;
	y -= _other_vec.y;
	z -= _other_vec.z;
	return *this;
}

Math::Vec3 Math::Vec3::operator+(const float _value) const
{
	return Vec3(x + _value, y + _value, z + _value);
}

Math::Vec3 Math::Vec3::operator-(const float _value) const
{
	return Vec3(x - _value, y - _value, z - _value);
}

Math::Vec3 Math::Vec3::operator*(const float _value) const
{
	return Vec3(x * _value, y * _value, z * _value);
}

Math::Vec3 Math::Vec3::operator/(const float _value) const
{
	return Vec3(x / _value, y / _value, z / _value);
}

Math::Vec3& Math::Vec3::operator+=(const float _value)
{
	x += _value;
	y += _value;
	z += _value;
	return *this;
}

Math::Vec3& Math::Vec3::operator-=(const float _value)
{
	x -= _value;
	y -= _value;
	z -= _value;
	return *this;
}

Math::Vec3& Math::Vec3::operator*=(const float _value)
{
	x *= _value;
	y *= _value;
	z *= _value;
	return *this;
}

Math::Vec3& Math::Vec3::operator/=(const float _value)
{
	x /= _value;
	y /= _value;
	z /= _value;
	return *this;
}

Math::Vec3 Math::Vec3::operator-() const
{
	return { -x, -y, -z };
}

float Math::Vec3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

Math::Vec3& Math::Vec3::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

Math::Vec3 Math::Vec3::Normalized() const
{
	return Vec3(x, y, z).Normalize();
}

float Math::Vec3::Dot(const Vec3 _other_vec) const
{
	return x * _other_vec.x + y * _other_vec.y + z * _other_vec.z;
}

Math::Vec3 Math::Vec3::Cross(Vec3 const _other_vec) const
{
	return {(y * _other_vec.z - z * _other_vec.y), (z * _other_vec.x - x * _other_vec.z), (x * _other_vec.y - y * _other_vec.x)};
}

float Math::Vec3::Angle(Vec3 _other_vec) const
{
	return acos(Dot(_other_vec) / (Length() * _other_vec.Length()));
}
