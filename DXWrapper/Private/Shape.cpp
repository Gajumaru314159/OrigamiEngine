#include "pch.h"
#include "Shape.h"

#include <cassert>

namespace og
{
	Shape::Shape(const U32 stribeSize):ms_StribeSize(stribeSize),m_IsChanged(false)
	{
		assert(0 < stribeSize);
	}


	S32 Shape::Draw(ComPtr<ID3D12Device>& device, ComPtr<ID3D12GraphicsCommandList>& commandList)
	{
		if (CheckArgs(device,commandList))return -1;

		if (m_IsChanged) {
			CreateResource(device);
		}

		if (IsValid()==false) return -1;


		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->IASetVertexBuffers(0, 1, &m_VertexBufferView);
		if (m_IndexBuffer)
		{
			commandList->IASetIndexBuffer(&m_IndexBufferView);
			commandList->DrawIndexedInstanced((UINT)m_Indices.size(), 1, 0, 0, 0);
		}
		else
		{
			commandList->DrawInstanced((UINT)m_Indices.size(), 1, 0, 0);
		}
		return 0;
	}



	S32 Shape::Vertex(const Byte* bytes, const U32 size)
	{
		if (bytes == nullptr)return -1;
		U32 currentSize = (U32)m_Bytes.size();
		U32 byteSize = size*ms_StribeSize;
		m_Bytes.resize(currentSize + byteSize);
		memcpy_s(m_Bytes.data() + currentSize, byteSize, bytes, byteSize);
		m_IsChanged = true;
		return 0;
	}

	S32 Shape::Indices(const U32 index1, const U32 index2, const U32 index3)
	{
		m_Indices.push_back(index1);
		m_Indices.push_back(index2);
		m_Indices.push_back(index3);
		m_IsChanged = true;
		return 0;
	}
	S32 Shape::Indices(const U32* indices, const U32 count)
	{
		if (indices == nullptr)return -1;
		U32 currentSize = (U32)m_Indices.size();
		m_Indices.resize(currentSize + count);
		memcpy_s(m_Indices.data() + currentSize, sizeof(U32)*count, indices, sizeof(U32) * count);
		m_IsChanged = true;
		return 0;
	}

	S32 Shape::GetStribeSize()
	{
		return ms_StribeSize;
	}
	S32 Shape::GetVertexCount()
	{
		return (S32)(m_Bytes.size() / ms_StribeSize);
	}
	S32 Shape::GetIndexCount()
	{
		return (S32)m_Indices.size();
	}



	S32 Shape::CreateResource(ComPtr<ID3D12Device>& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = m_Bytes.size();
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;


		//UPLOAD(確保は可能)
		auto result = device->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_VertexBuffer.ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
			return -1;
		}


		Byte* vertMap = nullptr;
		result = m_VertexBuffer->Map(0, nullptr, (void**)&vertMap);

		memcpy_s(vertMap, m_Bytes.size(), m_Bytes.data(), m_Bytes.size());

		m_VertexBuffer->Unmap(0, nullptr);

		m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();//バッファの仮想アドレス
		m_VertexBufferView.SizeInBytes = (UINT)m_Bytes.size();//全バイト数
		m_VertexBufferView.StrideInBytes = ms_StribeSize;//1頂点あたりのバイト数

		if (m_Indices.empty())return -1;
		// インデックス指定がある場合

		resdesc.Width = sizeof(U32) * m_Indices.size();
		result = device->CreateCommittedResource(
			&heapprop,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_IndexBuffer.ReleaseAndGetAddressOf()));

		//作ったバッファにインデックスデータをコピー
		U32* mappedIdx = nullptr;
		m_IndexBuffer->Map(0, nullptr, (void**)&mappedIdx);
		memcpy_s(mappedIdx, sizeof(U32) * m_Indices.size(), m_Indices.data(), sizeof(U32) * m_Indices.size());

		m_IndexBuffer->Unmap(0, nullptr);

		//インデックスバッファビューを作成
		m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
		m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
		m_IndexBufferView.SizeInBytes = sizeof(U32) * (U32)m_Indices.size();
		return 0;
	}
}