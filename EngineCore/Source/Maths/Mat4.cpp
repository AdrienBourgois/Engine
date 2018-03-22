#include "Mat4.h"

#include "Constants.h"
#include <cmath>

Math::Mat4::Mat4(const float _0, const float _1, const float _2, const float _3, const float _4, const float _5, const float _6, const float _7, const float _8, const float _9, const float _10, const float _11, const float _12, const float _13, const float _14, const float _15)
{
	values[0] = _0;		values[1] = _1;		values[2] = _2;		values[3] = _3;
	values[4] = _4;		values[5] = _5;		values[6] = _6;		values[7] = _7;
	values[8] = _8;		values[9] = _9;		values[10] = _10;	values[11] = _11;
	values[12] = _12;	values[13] = _13;	values[14] = _14;	values[15] = _15;
}

Math::Mat4::Mat4(const float _values[16])
{
	for (int i = 0; i < 16; ++i)
		values[i] = _values[i];
}

Math::Mat4& Math::Mat4::operator=(Mat4 const& _other_mat)
{
	for (int i = 0; i < 16; ++i)
		values[i] = _other_mat.values[i];

	return *this;
}

Math::Mat4& Math::Mat4::operator=(const float _value)
{
	for (float& value : values)
		value = _value;

	return *this;
}

Math::Mat4 const Math::Mat4::Identity =
{
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

float& Math::Mat4::operator[](const int _element)
{
	return values[_element];
}

bool Math::Mat4::operator==(Mat4 const& _other_mat) const
{
	for (int i = 0; i < 16; ++i)
		if (values[i] != _other_mat.values[i])
			return false;

	return true;
}

bool Math::Mat4::operator!=(const Mat4 _other_mat) const
{
	return !operator==(_other_mat);
}

Math::Mat4::operator bool() const
{
	for (const float value : values)
		if(value)
			return true;

	return false;
}

Math::Mat4 Math::Mat4::operator+(Mat4 const& _other_mat) const
{
	Mat4 result(*this);

	for (int i = 0; i < 16; ++i)
		result.values[i] += _other_mat.values[i];

	return result;
}

Math::Mat4 Math::Mat4::operator-(Mat4 const& _other_mat) const
{
	Mat4 result(*this);

	for (int i = 0; i < 16; ++i)
		result.values[i] -= _other_mat.values[i];

	return result;
}

Math::Mat4 Math::Mat4::operator*(Mat4 const& _other_mat) const
{
	Mat4 result;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				result.values[4 * i + j] += values[4 * i + k] * _other_mat.values[4 * k + j];

	return result;
}

Math::Mat4& Math::Mat4::operator+=(Mat4 const& _other_mat)
{
	*this = Mat4(*this) + _other_mat;
	return *this;
}

Math::Mat4& Math::Mat4::operator-=(Mat4 const& _other_mat)
{
	*this = Mat4(*this) - _other_mat;
	return *this;
}

Math::Mat4& Math::Mat4::operator*=(Mat4 const& _other_mat)
{
	*this = Mat4(*this) * _other_mat;
	return *this;
}

Math::Mat4 Math::Mat4::operator+(const float _value) const
{
	Mat4 result(*this);

	for (float& value : result.values)
		value += _value;

	return result;
}

Math::Mat4 Math::Mat4::operator-(const float _value) const
{
	Mat4 result(*this);

	for (float& value : result.values)
		value -= _value;

	return result;
}

Math::Mat4 Math::Mat4::operator*(const float _value) const
{
	Mat4 result(*this);

	for (float& value : result.values)
		value *= _value;

	return result;
}

Math::Mat4 Math::Mat4::operator/(const float _value) const
{
	Mat4 result(*this);

	for (float& value : result.values)
		value /= _value;

	return result;
}

Math::Mat4& Math::Mat4::operator+=(const float _value)
{
	for (float& value : values)
		value += _value;

	return *this;
}

Math::Mat4& Math::Mat4::operator-=(const float _value)
{
	for (float& value : values)
		value -= _value;

	return *this;
}

Math::Mat4& Math::Mat4::operator*=(const float _value)
{
	for (float& value : values)
		value *= _value;

	return *this;
}

Math::Mat4& Math::Mat4::operator/=(const float _value)
{
	for (float& value : values)
		value /= _value;

	return *this;
}

Math::Mat4 Math::Mat4::Translate(const float _x, const float _y, const float _z)
{
	return
	{
		1.f, 0.f, 0.f, _x,
		0.f, 1.f, 0.f, _y,
		0.f, 0.f, 1.f, _z,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::Translate(const Vec3 _translation)
{
	return
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		_translation.x, _translation.y, _translation.z, 1.f
	};
}

Math::Mat4 Math::Mat4::Scale(const float _x, const float _y, const float _z)
{
	return
	{
		_x, 0.f, 0.f, 0.f,
		0.f, _y, 0.f, 0.f,
		0.f, 0.f, _z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::Scale(const Vec3 _scale)
{
	return
	{
		_scale.x, 0.f, 0.f, 0.f,
		0.f, _scale.y, 0.f, 0.f,
		0.f, 0.f, _scale.z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::Scale(const float _scale)
{
	return
	{
		_scale, 0.f, 0.f, 0.f,
		0.f, _scale, 0.f, 0.f,
		0.f, 0.f, _scale, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::RotateX(const float _angle)
{
	const float angle_radian = Deg2Rad(_angle);

	return
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, cos(angle_radian), -sin(angle_radian), 0.f,
		0.f, sin(angle_radian), cos(angle_radian), 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::RotateY(const float _angle)
{
	const float angle_radian = Deg2Rad(_angle);

	return
	{
		cos(angle_radian), 0.f, sin(angle_radian), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(angle_radian), 0.f, cos(angle_radian), 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::RotateZ(const float _angle)
{
	const float angle_radian = Deg2Rad(_angle);

	return
	{
		cos(angle_radian), -sin(angle_radian), 0.f, 0.f,
		sin(angle_radian), cos(angle_radian), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

Math::Mat4 Math::Mat4::Rotate(const Vec3 _rotation)
{
	return Identity * RotateX(_rotation.x) * RotateY(_rotation.y) * RotateZ(_rotation.z);
}

bool Math::Mat4::IsOrthogonal() const
{
	return *this * GetTranspose() == Identity;
}

Math::Mat4 Math::Mat4::GetInverse() const
{
	Mat4 result;

	result.values[0] =   values[5]  * values[10] * values[15] -
							values[5]  * values[11] * values[14] -
							values[9]  * values[6]  * values[15] +
							values[9]  * values[7]  * values[14] +
							values[13] * values[6]  * values[11] -
							values[13] * values[7]  * values[10];

	result.values[4] =  -values[4]  * values[10] * values[15] +
							values[4]  * values[11] * values[14] +
							values[8]  * values[6]  * values[15] -
							values[8]  * values[7]  * values[14] -
							values[12] * values[6]  * values[11] +
							values[12] * values[7]  * values[10];

	result.values[8] =   values[4]  * values[9] * values[15] -
							values[4]  * values[11] * values[13] -
							values[8]  * values[5] * values[15] +
							values[8]  * values[7] * values[13] +
							values[12] * values[5] * values[11] -
							values[12] * values[7] * values[9];

	result.values[12] = -values[4]  * values[9] * values[14] +
							values[4]  * values[10] * values[13] +
							values[8]  * values[5] * values[14] -
							values[8]  * values[6] * values[13] -
							values[12] * values[5] * values[10] +
							values[12] * values[6] * values[9];

	result.values[1] =  -values[1]  * values[10] * values[15] +
							values[1]  * values[11] * values[14] +
							values[9]  * values[2] * values[15] -
							values[9]  * values[3] * values[14] -
							values[13] * values[2] * values[11] +
							values[13] * values[3] * values[10];

	result.values[5] =   values[0]  * values[10] * values[15] -
							values[0]  * values[11] * values[14] -
							values[8]  * values[2] * values[15] +
							values[8]  * values[3] * values[14] +
							values[12] * values[2] * values[11] -
							values[12] * values[3] * values[10];

	result.values[9] =  -values[0]  * values[9] * values[15] +
							values[0]  * values[11] * values[13] +
							values[8]  * values[1] * values[15] -
							values[8]  * values[3] * values[13] -
							values[12] * values[1] * values[11] +
							values[12] * values[3] * values[9];

	result.values[13] =  values[0]  * values[9] * values[14] -
							values[0]  * values[10] * values[13] -
							values[8]  * values[1] * values[14] +
							values[8]  * values[2] * values[13] +
							values[12] * values[1] * values[10] -
							values[12] * values[2] * values[9];

	result.values[2] =   values[1]  * values[6] * values[15] -
							values[1]  * values[7] * values[14] -
							values[5]  * values[2] * values[15] +
							values[5]  * values[3] * values[14] +
							values[13] * values[2] * values[7] -
							values[13] * values[3] * values[6];

	result.values[6] =  -values[0]  * values[6] * values[15] +
							values[0]  * values[7] * values[14] +
							values[4]  * values[2] * values[15] -
							values[4]  * values[3] * values[14] -
							values[12] * values[2] * values[7] +
							values[12] * values[3] * values[6];

	result.values[10] =  values[0]  * values[5] * values[15] -
							values[0]  * values[7] * values[13] -
							values[4]  * values[1] * values[15] +
							values[4]  * values[3] * values[13] +
							values[12] * values[1] * values[7] -
							values[12] * values[3] * values[5];

	result.values[14] = -values[0]  * values[5] * values[14] +
							values[0]  * values[6] * values[13] +
							values[4]  * values[1] * values[14] -
							values[4]  * values[2] * values[13] -
							values[12] * values[1] * values[6] +
							values[12] * values[2] * values[5];

	result.values[3] =  -values[1] * values[6] * values[11] +
							values[1] * values[7] * values[10] +
							values[5] * values[2] * values[11] -
							values[5] * values[3] * values[10] -
							values[9] * values[2] * values[7] +
							values[9] * values[3] * values[6];

	result.values[7] =   values[0] * values[6] * values[11] -
							values[0] * values[7] * values[10] -
							values[4] * values[2] * values[11] +
							values[4] * values[3] * values[10] +
							values[8] * values[2] * values[7] -
							values[8] * values[3] * values[6];

	result.values[11] = -values[0] * values[5] * values[11] +
							values[0] * values[7] * values[9] +
							values[4] * values[1] * values[11] -
							values[4] * values[3] * values[9] -
							values[8] * values[1] * values[7] +
							values[8] * values[3] * values[5];

	result.values[15] =  values[0] * values[5] * values[10] -
							values[0] * values[6] * values[9] -
							values[4] * values[1] * values[10] +
							values[4] * values[2] * values[9] +
							values[8] * values[1] * values[6] -
							values[8] * values[2] * values[5];

	float determinant = values[0] * result.values[0] + values[1] * result.values[4] + values[2] * result.values[8] + values[3] * result.values[12];

	if (determinant != 0.f)
	{
		determinant = 1.0f / determinant;

		for (float& value : result.values)
			value *= determinant;
	}

	return result;
}

Math::Mat4& Math::Mat4::Transpose()
{
	operator=(Mat4(*this).GetTranspose());
	return *this;
}

Math::Mat4 Math::Mat4::GetTranspose() const
{
	return
	{
		values[0], values[4], values[8], values[12],
		values[1], values[5], values[9], values[13],
		values[2], values[6], values[10], values[14],
		values[3], values[7], values[11], values[15]
	};
}

Math::Mat4 Math::Mat4::PerspectiveMatrix(const float _angle_of_view, const float _aspect_ratio, const float _near, const float _far)
{
	Mat4 matrix;

	const float h = 1.f / tanf(_angle_of_view * 0.5f);

	matrix.values[0] = h / _aspect_ratio;
	matrix.values[5] = h;
	matrix.values[10] = _far / (_far - _near);
	matrix.values[11] = 1;
	matrix.values[14] = -_near * _far / (_far - _near);

	return matrix;
}

Math::Mat4 Math::Mat4::LookAt(const Vec3 _eye, const Vec3 _target, const Vec3 _up)
{
	const Vec3 z_axis = Vec3(_target - _eye).Normalized();
	const Vec3 x_axis = Vec3(_up.Cross(z_axis)).Normalized();
	const Vec3 y_axis = Vec3(z_axis.Cross(x_axis));

	return
	{
		x_axis.x, y_axis.x, z_axis.x, 0,
		x_axis.y, y_axis.y, z_axis.y, 0,
		x_axis.z, y_axis.z, z_axis.z, 0,
		-Vec3(x_axis).Dot(_eye), -Vec3(y_axis).Dot(_eye), -Vec3(z_axis).Dot(_eye), 1
	};
}
