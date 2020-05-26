#include "pch.h"
#include "Shape.h"

namespace og
{
	Shape::Shape(ComPtr<ID3D12Device>& device, const U32 stribeSize, const U32 dataSize, const Byte* data, const U32 indexNum, const U32* indicis)
	{
		if (stribeSize == 0)return;
		if (dataSize % stribeSize != 0)return;


		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = dataSize;
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
			return;
		}


		Byte* vertMap = nullptr;
		result = m_VertexBuffer->Map(0, nullptr, (void**)&vertMap);

		memcpy_s(vertMap, dataSize, data, dataSize);

		m_VertexBuffer->Unmap(0, nullptr);

		m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();//バッファの仮想アドレス
		m_VertexBufferView.SizeInBytes = dataSize;//全バイト数
		m_VertexBufferView.StrideInBytes = stribeSize;//1頂点あたりのバイト数

		m_IndexNum = dataSize / stribeSize;




		if (indexNum == 0 || indicis == nullptr)return;
		// インデックス指定がある場合

		resdesc.Width = sizeof(U32) * indexNum;
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
		memcpy_s(mappedIdx, sizeof(U32) * indexNum, indicis, sizeof(U32) * indexNum);

		m_IndexBuffer->Unmap(0, nullptr);

		//インデックスバッファビューを作成
		m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
		m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
		m_IndexBufferView.SizeInBytes = sizeof(U32) * indexNum;

		m_IndexNum = indexNum;
	}


	S32 Shape::Draw(ComPtr<ID3D12GraphicsCommandList>& commandList)const
	{
		if (CheckArgs(commandList))return -1;
		if (!IsValid())return -1;

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		if (m_VertexBuffer)commandList->IASetVertexBuffers(0, 1, &m_VertexBufferView);
		if (m_IndexBuffer)
		{
			commandList->IASetIndexBuffer(&m_IndexBufferView);
			commandList->DrawIndexedInstanced(m_IndexNum, 1, 0, 0, 0);
		}
		else
		{
			commandList->DrawInstanced(m_IndexNum, 1, 0, 0);
		}
		return 0;
	}
}