#include "Vertex.h"

Core::CoreType::Vertex::Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a)
{
	data[0] = _x;
	data[1] = _y;
	data[2] = _z;
	data[3] = _r;
	data[4] = _g;
	data[5] = _b;
	data[6] = _a;
}

Core::CoreType::Vertex::Vertex(float _x, float _y, float _z, Color _color)
{
	data[0] = _x;
	data[1] = _y;
	data[2] = _z;

	data[3] = _color.r;
	data[4] = _color.g;
	data[5] = _color.b;
	data[6] = _color.a;
}

Core::CoreType::Vertex::Vertex(Math::Vec3 _location, float _r, float _g, float _b, float _a)
{
	data[0] = _location.x;
	data[1] = _location.y;
	data[2] = _location.z;

	data[3] = _r;
	data[4] = _g;
	data[5] = _b;
	data[6] = _a;
}

Core::CoreType::Vertex::Vertex(Math::Vec3 _location, Color _color)
{
	data[0] = _location.x;
	data[1] = _location.y;
	data[2] = _location.z;

	data[3] = _color.r;
	data[4] = _color.g;
	data[5] = _color.b;
	data[6] = _color.a;
}

Core::CoreType::Vertex::Vertex(Math::Vec3 _location)
{
	data[0] = _location.x;
	data[1] = _location.y;
	data[2] = _location.z;
}

Core::CoreType::Vertex::Vertex(Color _color)
{
	data[3] = _color.r;
	data[4] = _color.g;
	data[5] = _color.b;
	data[6] = _color.a;
}

void Core::CoreType::Vertex::SetLocation(Math::Vec3 _new_location)
{
	data[0] = _new_location.x;
	data[1] = _new_location.y;
	data[2] = _new_location.z;
}

void Core::CoreType::Vertex::SetColor(Color _new_color)
{
	data[3] = _new_color.r;
	data[4] = _new_color.g;
	data[5] = _new_color.b;
	data[6] = _new_color.a;
}
