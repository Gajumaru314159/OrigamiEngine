#include "pch.h"
#include "Shape.h"

#include <cassert>

#include "DX12Wrapper.h"

namespace og
{
	Shape::Shape(const U32 stribeSize) :ms_stribeSize(stribeSize), m_isChanged(false)
	{
		assert(0 < stribeSize);
	}


	S32 Shape::Draw(ComPtr<ID3D12GraphicsCommandList>& commandList, const U32 count)
	{
		if (CheckArgs(commandList))return -1;

		if (m_isChanged)
		{
			CreateResource();
			m_isChanged = false;
		}

		if (IsValid() == false) return -1;


		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
		if (m_indexBuffer)
		{
			commandList->IASetIndexBuffer(&m_indexBufferView);
			commandList->DrawIndexedInstanced((UINT)m_indices.size(), count, 0, 0, 0);
		}
		else
		{
			commandList->DrawInstanced((UINT)m_indices.size(), 1, 0, 0);
		}



		return 0;
	}



	S32 Shape::Vertex(const Byte* bytes, const U32 size)
	{
		if (bytes == nullptr)return -1;
		U32 currentSize = (U32)m_data.size();
		U32 byteSize = size * ms_stribeSize;
		m_data.resize(currentSize + byteSize);
		memcpy_s(m_data.data() + currentSize, byteSize, bytes, byteSize);
		m_isChanged = true;
		return 0;
	}

	S32 Shape::Indices(const U32 index1, const U32 index2, const U32 index3)
	{
		m_indices.push_back(index1);
		m_indices.push_back(index2);
		m_indices.push_back(index3);
		m_isChanged = true;
		return 0;
	}
	S32 Shape::Indices(const U32* indices, const U32 count)
	{
		if (indices == nullptr)return -1;
		U32 currentSize = (U32)m_indices.size();
		m_indices.resize(currentSize + count);
		memcpy_s(m_indices.data() + currentSize, sizeof(U32) * count, indices, sizeof(U32) * count);
		m_isChanged = true;
		return 0;
	}

	S32 Shape::GetStribeSize()
	{
		return ms_stribeSize;
	}
	S32 Shape::GetVertexCount()
	{
		return (S32)(m_data.size() / ms_stribeSize);
	}
	S32 Shape::GetIndexCount()
	{
		return (S32)m_indices.size();
	}



	S32 Shape::CreateResource()
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = m_data.size();
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;


		ComPtr<ID3D12Resource> vertexBuffer;

		//UPLOAD(確保は可能)
		auto result = DX12Wrapper::ms_device->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(vertexBuffer.ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
			return -1;
		}


		Byte* vertMap = nullptr;
		result = vertexBuffer->Map(0, nullptr, (void**)&vertMap);

		memcpy_s(vertMap, m_data.size(), m_data.data(), m_data.size());

		vertexBuffer->Unmap(0, nullptr);

		m_vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();//バッファの仮想アドレス
		m_vertexBufferView.SizeInBytes = (UINT)m_data.size();//全バイト数
		m_vertexBufferView.StrideInBytes = ms_stribeSize;//1頂点あたりのバイト数

		if (m_indices.empty())
		{
			m_vertexBuffer = vertexBuffer;
			return 0;
		}
		// インデックス指定がある場合

		resdesc.Width = sizeof(U32) * m_indices.size();
		result = DX12Wrapper::ms_device->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_indexBuffer.ReleaseAndGetAddressOf()));

		//作ったバッファにインデックスデータをコピー
		U32* mappedIdx = nullptr;
		m_indexBuffer->Map(0, nullptr, (void**)&mappedIdx);
		memcpy_s(mappedIdx, sizeof(U32) * m_indices.size(), m_indices.data(), sizeof(U32) * m_indices.size());

		m_indexBuffer->Unmap(0, nullptr);

		//インデックスバッファビューを作成
		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		m_indexBufferView.SizeInBytes = sizeof(U32) * (U32)m_indices.size();


		m_vertexBuffer = vertexBuffer;
		return 0;
	}
}