#pragma once

struct Vec3
{
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float x = 0;
	float y = 0;
	float z = 0;
};

struct Vec4
{
	Vec4(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;
};

struct Vertex
{
	Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a) : pos(_x, _y, _z), color(_r, _g, _b, _a) {}

	Vec3 pos;
	Vec4 color;
};