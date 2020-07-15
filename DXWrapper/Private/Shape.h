#pragma once

#include "IShape.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	class Shape :public IShape
	{
	private:
		ComPtr<ID3D12Resource> m_VertexBuffer;
		ComPtr<ID3D12Resource> m_IndexBuffer;

		D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;
		D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

		const U32 ms_StribeSize;

		ArrayList<Byte> m_Bytes;
		ArrayList<U32> m_Indices;

		bool m_IsChanged;

	public:
		Shape(const U32 stribeSize);

		S32 Draw(ComPtr<ID3D12GraphicsCommandList>& commandList, const U32 count = 1);

		inline bool IsValid()const { return m_VertexBuffer != nullptr; }


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