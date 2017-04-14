#pragma once

#include "Core/CoreType/Vertex.h"
#include "Core/CoreType/Id.h"

class TempObject
{
public:
	TempObject() = default;

	explicit TempObject(Core::CoreType::Vertex _points[], int _size);

	Core::CoreType::Vertex* GetPoints();
	size_t GetSize() const;
	uint16_t GetId();

private:
	std::vector<Core::CoreType::Vertex> vertexs;
	Core::CoreType::Id id = Core::CoreType::Id(Core::CoreType::EObjectSubtype::DefaultGameObject);
};
