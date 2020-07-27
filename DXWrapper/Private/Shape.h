#pragma once

#include "IShape.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	class Shape :public IShape
	{
	private:
		ComPtr<ID3D12Resource> m_vertexBuffer;
		ComPtr<ID3D12Resource> m_indexBuffer;

		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

		const U32 ms_stribeSize;

		ArrayList<Byte> m_data;
		ArrayList<U32> m_indices;

		bool m_isChanged;

	public:
		Shape(const U32 stribeSize);

		S32 Draw(ComPtr<ID3D12GraphicsCommandList>& commandList, const U32 count = 1);

		inline bool IsValid()const { return m_vertexBuffer != nullptr; }


		S32 Vertex(const Byte* bytes, const U32 size)override;
		S32 Indices(const U32 index1, const U32 index2, const U32 index3)override;
		S32 Indices(const U32* indices, const U32 count)override;

		S32 GetStribeSize()override;
		S32 GetVertexCount()override;
		S32 GetIndexCount()override;
	private:
		S32 CreateResource();

	};
}