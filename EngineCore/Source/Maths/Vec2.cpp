#include "Vec2.h"
#include <cmath>

Math::Vec2::Vec2(float _value): x(_value), y(_value)
{}

Math::Vec2::Vec2(float _x, float _y): x(_x), y(_y)
{}

void Math::Vec2::operator=(Vec2 _other_vector)
{
	x = _other_vector.x;
	y = _other_vector.y;
}

bool Math::Vec2::operator==(Vec2 _other_vec) const
{
	if(x == _other_vec.x && y == _other_vec.y)
		return true;
	return false;
}

bool Math::Vec2::operator!=(Vec2 _other_vec) const
{
	return !operator==(_other_vec);
}

Math::Vec2 Math::Vec2::operator+(Vec2 _other_vec) const
{
	Vec2 result_vec;
	result_vec.x = x + _other_vec.x;
	result_vec.y = y + _other_vec.y;
	return result_vec;
}

Math::Vec2 Math::Vec2::operator-(Vec2 _other_vec) const
{
	Vec2 result_vec;
	result_vec.x = x - _other_vec.x;
	result_vec.y = y - _other_vec.y;
	return result_vec;
}

void Math::Vec2::operator+=(Vec2 _other_vec)
{
	x += _other_vec.x;
	y += _other_vec.y;
}

void Math::Vec2::operator-=(Vec2 _other_vec)
{
	x -= _other_vec.x;
	y -= _other_vec.y;
}

Math::Vec2::operator bool() const
{
	if(x || y)
		return true;
	return false;
}

float Math::Vec2::Length() const
{
	return sqrt(x*x + y*y);
}

void Math::Vec2::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
}

Math::Vec2 Math::Vec2::Normalized() const
{
	Vec2 new_vector(x, y);
	float length = Length();
	new_vector.x /= length;
	new_vector.y /= length;
	return new_vector;
}

float Math::Vec2::Dot(Vec2 _other_vec) const
{
	return x*_other_vec.x + y*_other_vec.y;
}
