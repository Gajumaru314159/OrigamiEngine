#pragma once

#include <d3d12.h>
#include <wrl.h>


namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace og
{
	class Shape
	{
	private:

		ComPtr<ID3D12Resource> m_VertexBuffer;
		ComPtr<ID3D12Resource> m_IndexBuffer;

		D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;
		D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

		U32 m_IndexNum;

	public:
		Shape(ComPtr<ID3D12Device>& device, const U32 stribeSize, const U32 dataSize, const Byte* data, const U32 indexNum = 0, const U32* indicis = nullptr);

		S32 Draw(ComPtr<ID3D12GraphicsCommandList>& commandList)const;

		inline bool IsValid()const { return m_VertexBuffer != nullptr; }
	};
}