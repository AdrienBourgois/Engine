#include "Vertex.h"

Core::CoreType::Vertex::Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a)
{
	datas[0] = _x;
	datas[1] = _y;
	datas[2] = _z;
	datas[3] = _r;
	datas[4] = _g;
	datas[5] = _b;
	datas[6] = _a;
}

Core::CoreType::Vertex::Vertex(Math::Vec3 _location, Color _color)
{
	datas[0] = _location.x;
	datas[1] = _location.y;
	datas[2] = _location.z;

	datas[3] = _color.r;
	datas[4] = _color.g;
	datas[5] = _color.b;
	datas[6] = _color.a;
}

Core::CoreType::Vertex::Vertex(Math::Vec3 _location)
{
	datas[0] = _location.x;
	datas[1] = _location.y;
	datas[2] = _location.z;
}

Core::CoreType::Vertex::Vertex(Color _color)
{
	datas[3] = _color.r;
	datas[4] = _color.g;
	datas[5] = _color.b;
	datas[6] = _color.a;
}

void Core::CoreType::Vertex::SetLocation(Math::Vec3 _new_location)
{
	datas[0] = _new_location.x;
	datas[1] = _new_location.y;
	datas[2] = _new_location.z;
}

void Core::CoreType::Vertex::SetColor(Color _new_color)
{
	datas[3] = _new_color.r;
	datas[4] = _new_color.g;
	datas[5] = _new_color.b;
	datas[6] = _new_color.a;
}
