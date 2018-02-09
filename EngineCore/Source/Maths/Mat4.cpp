#include "Mat4.h"

#include "Constants.h"
#include <cmath>

namespace Math
{
	Mat4 const Mat4::Identity =	Mat4({
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	});

	Mat4::Mat4()
	{
		for (int i = 0; i < 16; ++i)
			Values[i] = 0.f;
	}

	Mat4::Mat4(float _0, float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15)
	{
		Values[0] = _0;		Values[1] = _1;		Values[2] = _2;		Values[3] = _3;
		Values[4] = _4;		Values[5] = _5;		Values[6] = _6;		Values[7] = _7;
		Values[8] = _8;		Values[9] = _9;		Values[10] = _10;	Values[11] = _11;
		Values[12] = _12;	Values[13] = _13;	Values[14] = _14;	Values[15] = _15;
	}

	Mat4::Mat4(float _values[16])
	{
		for (int i = 0; i < 16; ++i)
			Values[i] = _values[i];
	}

	Mat4 const Mat4::PerspectiveMatrix(const float _angle_of_view, const float _aspect_ratio, const float _near, const float _far)
	{
		Mat4 matrix;

		float h = 1.f / tanf(_angle_of_view * 0.5f);

		matrix.Values[0] = h / _aspect_ratio;
		matrix.Values[5] = h;
		matrix.Values[10] = _far / (_far - _near);
		matrix.Values[11] = 1;
		matrix.Values[14] = -_near * _far / (_far - _near);

		return matrix;
	}

	Mat4 const Mat4::LookAt(const Vec3 _eye, const Vec3 _target, const Vec3 _up)
	{
		Vec3 z_axis = Vec3(_target - _eye).Normalized();
		Vec3 x_axis = Vec3(_up.Cross(z_axis)).Normalized();
		Vec3 y_axis = Vec3(z_axis.Cross(x_axis));

		Mat4 viewMatrix = {
			x_axis.x, y_axis.x, z_axis.x, 0 ,
			x_axis.y, y_axis.y, z_axis.y, 0 ,
			x_axis.z, y_axis.z, z_axis.z, 0 ,
			-Vec3(x_axis).Dot(_eye), -Vec3(y_axis).Dot(_eye), -Vec3(z_axis).Dot(_eye), 1
		};

		return viewMatrix;
	}

	Mat4 Mat4::Translate(float _x, float _y, float _z)
	{
		return Mat4({
			1.f, 0.f, 0.f, _x,
			0.f, 1.f, 0.f, _y,
			0.f, 0.f, 1.f, _z,
			0.f, 0.f, 0.f, 1.f
		});
	}

	Mat4 Mat4::Translate(Vec3 _translation)
	{
		return Mat4({
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			_translation.x, _translation.y, _translation.z, 1.f
		});
	}

	Mat4 Mat4::Scale(float _x, float _y, float _z)
	{
		return Mat4({
			_x, 0.f, 0.f, 0.f,
			0.f, _y, 0.f, 0.f,
			0.f, 0.f, _z, 0.f,
			0.f, 0.f, 0.f, 1.f
		});
	}

	Mat4 Mat4::Scale(Vec3 _scale)
	{
		return Mat4({
			_scale.x, 0.f, 0.f, 0.f,
			0.f, _scale.y, 0.f, 0.f,
			0.f, 0.f, _scale.z, 0.f,
			0.f, 0.f, 0.f, 1.f
		});
	}

	Mat4 Mat4::Scale(float _scale)
	{
		return Mat4({
			_scale, 0.f, 0.f, 0.f,
			0.f, _scale, 0.f, 0.f,
			0.f, 0.f, _scale, 0.f,
			0.f, 0.f, 0.f, 1.f
		});
	}

	Mat4 Mat4::RotateX(float _angle)
	{
		float angle_radian = Deg2Rad(_angle);

		return Mat4({
			1.f, 0.f, 0.f, 0.f,
			0.f, cos(angle_radian), -sin(angle_radian), 0.f,
			0.f, sin(angle_radian), cos(angle_radian), 0.f,
			0.f, 0.f, 0.f, 1.f
		});
	}

	auto Mat4::RotateY(float _angle) -> Mat4
	{
		float angle_radian = Deg2Rad(_angle);

		return Mat4({
			cos(angle_radian) , 0.f, sin(angle_radian), 0.f,
			0.f , 1.f, 0.f, 0.f,
			-sin(angle_radian), 0.f, cos(angle_radian), 0.f,
			0.f , 0.f, 0.f, 1.f
		});
	}

	auto Mat4::RotateZ(float _angle) -> Mat4
	{
		float angle_radian = Deg2Rad(_angle);

		return Mat4({
			cos(angle_radian), -sin(angle_radian), 0.f, 0.f,
			sin(angle_radian), cos(angle_radian), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		});
	}

	Mat4 Mat4::Rotate(Vec3 _rotation)
	{
		return Identity * RotateX(_rotation.x) * RotateY(_rotation.y) * RotateZ(_rotation.z);
	}

	float& Mat4::operator[](int _element)
	{
		return Values[_element];
	}

	bool Mat4::operator==(Mat4 _other) const
	{
		for (int i = 0; i < 16; ++i)
			if (Values[i] != _other[i])
				return false;

		return true;
	}

	bool Mat4::operator!=(Mat4 _other) const
	{
		for (int i = 0; i < 16; ++i)
			if (Values[i] != _other[i])
				return true;

		return false;
	}

	Mat4 Mat4::operator*(Mat4 const& _matrix) const
	{
		Mat4 result = Mat4();

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					result.Values[4 * i + j] += Values[4 * i + k] * _matrix.Values[4 * k + j];

		return result;
	}

	void Mat4::operator*=(Mat4 const& _matrix)
	{
		*this = *this * _matrix;
	}

	bool Mat4::IsOrthogonal()
	{
		Mat4 temp_matrix(this->Values);

		return temp_matrix * temp_matrix.GetTranspose() == Identity;
	}

	Mat4 Mat4::GetInverse() const
	{
		Mat4 result;

		result.Values[0] =   Values[5]  * Values[10] * Values[15] -
							 Values[5]  * Values[11] * Values[14] -
							 Values[9]  * Values[6]  * Values[15] +
							 Values[9]  * Values[7]  * Values[14] +
							 Values[13] * Values[6]  * Values[11] -
							 Values[13] * Values[7]  * Values[10];

		result.Values[4] =  -Values[4]  * Values[10] * Values[15] +
							 Values[4]  * Values[11] * Values[14] +
							 Values[8]  * Values[6]  * Values[15] -
							 Values[8]  * Values[7]  * Values[14] -
							 Values[12] * Values[6]  * Values[11] +
							 Values[12] * Values[7]  * Values[10];

		result.Values[8] =   Values[4]  * Values[9] * Values[15] -
							 Values[4]  * Values[11] * Values[13] -
							 Values[8]  * Values[5] * Values[15] +
							 Values[8]  * Values[7] * Values[13] +
							 Values[12] * Values[5] * Values[11] -
							 Values[12] * Values[7] * Values[9];

		result.Values[12] = -Values[4]  * Values[9] * Values[14] +
							 Values[4]  * Values[10] * Values[13] +
							 Values[8]  * Values[5] * Values[14] -
							 Values[8]  * Values[6] * Values[13] -
							 Values[12] * Values[5] * Values[10] +
							 Values[12] * Values[6] * Values[9];

		result.Values[1] =  -Values[1]  * Values[10] * Values[15] +
							 Values[1]  * Values[11] * Values[14] +
							 Values[9]  * Values[2] * Values[15] -
							 Values[9]  * Values[3] * Values[14] -
							 Values[13] * Values[2] * Values[11] +
							 Values[13] * Values[3] * Values[10];

		result.Values[5] =   Values[0]  * Values[10] * Values[15] -
							 Values[0]  * Values[11] * Values[14] -
							 Values[8]  * Values[2] * Values[15] +
							 Values[8]  * Values[3] * Values[14] +
							 Values[12] * Values[2] * Values[11] -
							 Values[12] * Values[3] * Values[10];

		result.Values[9] =  -Values[0]  * Values[9] * Values[15] +
							 Values[0]  * Values[11] * Values[13] +
							 Values[8]  * Values[1] * Values[15] -
							 Values[8]  * Values[3] * Values[13] -
							 Values[12] * Values[1] * Values[11] +
							 Values[12] * Values[3] * Values[9];

		result.Values[13] =  Values[0]  * Values[9] * Values[14] -
							 Values[0]  * Values[10] * Values[13] -
							 Values[8]  * Values[1] * Values[14] +
							 Values[8]  * Values[2] * Values[13] +
							 Values[12] * Values[1] * Values[10] -
							 Values[12] * Values[2] * Values[9];

		result.Values[2] =   Values[1]  * Values[6] * Values[15] -
							 Values[1]  * Values[7] * Values[14] -
							 Values[5]  * Values[2] * Values[15] +
							 Values[5]  * Values[3] * Values[14] +
							 Values[13] * Values[2] * Values[7] -
							 Values[13] * Values[3] * Values[6];

		result.Values[6] =  -Values[0]  * Values[6] * Values[15] +
							 Values[0]  * Values[7] * Values[14] +
							 Values[4]  * Values[2] * Values[15] -
							 Values[4]  * Values[3] * Values[14] -
							 Values[12] * Values[2] * Values[7] +
							 Values[12] * Values[3] * Values[6];

		result.Values[10] =  Values[0]  * Values[5] * Values[15] -
							 Values[0]  * Values[7] * Values[13] -
							 Values[4]  * Values[1] * Values[15] +
							 Values[4]  * Values[3] * Values[13] +
							 Values[12] * Values[1] * Values[7] -
							 Values[12] * Values[3] * Values[5];

		result.Values[14] = -Values[0]  * Values[5] * Values[14] +
							 Values[0]  * Values[6] * Values[13] +
							 Values[4]  * Values[1] * Values[14] -
							 Values[4]  * Values[2] * Values[13] -
							 Values[12] * Values[1] * Values[6] +
							 Values[12] * Values[2] * Values[5];

		result.Values[3] =  -Values[1] * Values[6] * Values[11] +
							 Values[1] * Values[7] * Values[10] +
							 Values[5] * Values[2] * Values[11] -
							 Values[5] * Values[3] * Values[10] -
							 Values[9] * Values[2] * Values[7] +
							 Values[9] * Values[3] * Values[6];

		result.Values[7] =   Values[0] * Values[6] * Values[11] -
							 Values[0] * Values[7] * Values[10] -
							 Values[4] * Values[2] * Values[11] +
							 Values[4] * Values[3] * Values[10] +
							 Values[8] * Values[2] * Values[7] -
							 Values[8] * Values[3] * Values[6];

		result.Values[11] = -Values[0] * Values[5] * Values[11] +
							 Values[0] * Values[7] * Values[9] +
							 Values[4] * Values[1] * Values[11] -
							 Values[4] * Values[3] * Values[9] -
							 Values[8] * Values[1] * Values[7] +
							 Values[8] * Values[3] * Values[5];

		result.Values[15] =  Values[0] * Values[5] * Values[10] -
							 Values[0] * Values[6] * Values[9] -
							 Values[4] * Values[1] * Values[10] +
							 Values[4] * Values[2] * Values[9] +
							 Values[8] * Values[1] * Values[6] -
							 Values[8] * Values[2] * Values[5];

		float determinant = Values[0] * result.Values[0] + Values[1] * result.Values[4] + Values[2] * result.Values[8] + Values[3] * result.Values[12];

		if (determinant != 0.f)
		{
			determinant = 1.0f / determinant;

			for (int i = 0; i < 16; i++)
				result.Values[i] *= determinant;
		}

		return result;
	}

	Mat4 Mat4::GetTranspose() const
	{
		return Mat4(Values[0], Values[4], Values[8], Values[12],
					Values[1], Values[5], Values[9], Values[13],
					Values[2], Values[6], Values[10], Values[14],
					Values[3], Values[7], Values[11], Values[15]);
	}
}
