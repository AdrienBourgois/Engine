#include "Vec2.h"
#include <cmath>

Math::Vec2::Vec2(const float _value): x(_value), y(_value) {}

Math::Vec2::Vec2(const float _x, const float _y): x(_x), y(_y) {}

Math::Vec2& Math::Vec2::operator=(const Vec2 _other_vec)
{
	x = _other_vec.x;
	y = _other_vec.y;
	return *this;
}

Math::Vec2& Math::Vec2::operator=(const float _value)
{
	x = _value;
	y = _value;
	return *this;
}

bool Math::Vec2::operator==(const Vec2 _other_vec) const
{
	return x == _other_vec.x && y == _other_vec.y;
}

bool Math::Vec2::operator!=(const Vec2 _other_vec) const
{
	return !operator==(_other_vec);
}

Math::Vec2::operator bool() const
{
	return x || y;
}

Math::Vec2 Math::Vec2::operator+(const Vec2 _other_vec) const
{
	Vec2 result_vec;
	result_vec.x = x + _other_vec.x;
	result_vec.y = y + _other_vec.y;
	return result_vec;
}

Math::Vec2 Math::Vec2::operator-(const Vec2 _other_vec) const
{
	Vec2 result_vec;
	result_vec.x = x - _other_vec.x;
	result_vec.y = y - _other_vec.y;
	return result_vec;
}

void Math::Vec2::operator+=(const Vec2 _other_vec)
{
	x += _other_vec.x;
	y += _other_vec.y;
}

void Math::Vec2::operator-=(const Vec2 _other_vec)
{
	x -= _other_vec.x;
	y -= _other_vec.y;
}

Math::Vec2 Math::Vec2::operator+(const float _value) const
{
	return Vec2(x + _value, y + _value);
}

Math::Vec2 Math::Vec2::operator-(const float _value) const
{
	return Vec2(x - _value, y - _value);
}

Math::Vec2 Math::Vec2::operator*(const float _value) const
{
	return Vec2(x * _value, y * _value);
}

Math::Vec2 Math::Vec2::operator/(const float _value) const
{
	return Vec2(x / _value, y / _value);
}

Math::Vec2& Math::Vec2::operator+=(const float _value)
{
	x += _value;
	y += _value;
	return *this;
}

Math::Vec2& Math::Vec2::operator-=(const float _value)
{
	x -= _value;
	y -= _value;
	return *this;
}

Math::Vec2& Math::Vec2::operator*=(const float _value)
{
	x *= _value;
	y *= _value;
	return *this;
}

Math::Vec2& Math::Vec2::operator/=(const float _value)
{
	x /= _value;
	y /= _value;
	return *this;
}

Math::Vec2 Math::Vec2::operator-() const
{
	return {-x, -y};
}

float Math::Vec2::Length() const
{
	return sqrt(x * x + y * y);
}

Math::Vec2& Math::Vec2::Normalize()
{
	const float length = Length();
	x /= length;
	y /= length;
	return *this;
}

Math::Vec2 Math::Vec2::Normalized() const
{
	return Vec2(x, y).Normalize();
}

float Math::Vec2::Dot(const Vec2 _other_vec) const
{
	return x * _other_vec.x + y * _other_vec.y;
}

float Math::Vec2::Angle(Vec2 _other_vec) const
{
	return acos(Dot(_other_vec) / (Length() * _other_vec.Length()));
}
