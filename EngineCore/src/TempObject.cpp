#include "TempObject.h"

TempObject::TempObject(Core::CoreType::Vertex _points[], int _size)
{
	for (int i = 0; i < _size; ++i)
	{
		vertexs.push_back(_points[i]);
	}
}

Core::CoreType::Vertex* TempObject::GetPoints()
{
	return vertexs.data();
}

size_t TempObject::GetSize() const
{
	return vertexs.size();
}

uint16_t TempObject::GetId()
{
	return id.GetInstanceNumber();
}
