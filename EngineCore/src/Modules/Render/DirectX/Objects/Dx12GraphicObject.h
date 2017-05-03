#pragma once

#include <d3d12.h>
#include "Core/CoreType/String.h"
#include "Core/CoreType/Vertex.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
   {                    \
	  x->Release();     \
	  x = NULL;         \
   }
#endif

namespace Core {
	namespace CoreType {
		class Vertex;
	}
}

namespace Module
{
	namespace Render
	{
		namespace DirectX12
		{
			namespace Objects
			{
				class Dx12GraphicObject
				{
				public:
					Dx12GraphicObject(unsigned int _id, const Core::CoreType::Vertex* _vertex, Core::CoreType::String _name, ID3D12GraphicsCommandList* _command_list, D3D12_VERTEX_BUFFER_VIEW* _buffer_view);
					~Dx12GraphicObject();

					void PrepareCommandList() const;

					unsigned GetId() const;
					ID3D12GraphicsCommandList* GetCommandList() const;
					D3D12_VERTEX_BUFFER_VIEW* GetBufferView() const;

				private:
					unsigned int id = 0;
					ID3D12GraphicsCommandList* commandList = nullptr;
					D3D12_VERTEX_BUFFER_VIEW* bufferView = nullptr;
					Core::CoreType::String name = S("Unnamed DX12 Graphic Object");

					Core::CoreType::Vertex* vertexs = nullptr;
					unsigned int size = 0;
					const Core::CoreType::Vertex* vertex;
				};
			}
		}
	}
}

