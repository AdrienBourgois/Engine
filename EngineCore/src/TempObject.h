#pragma once

#include "Core/CoreType/Vertex.h"

class TempObject
{
public:
	TempObject() = default;

	TempObject(Math::Vec3 _vec, Core::CoreType::Color _color, int _id) : vertex(_vec, _color), id(_id) {}

	Core::CoreType::Vertex vertex;
	int id = 0;
};
