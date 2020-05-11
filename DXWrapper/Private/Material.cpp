#include "pch.h"
#include "Material.h"

#include <d3dx12.h>

#include "GraphicPipeline.h"
#include "Texture.h"
#include "DefaultAsset.h"

namespace og
{
	Material::Material(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline, const S32 mask)
	{
		if (CheckArgs(device, !!gpipeline))return;
		m_IsChanged = true;
		m_DescriptorNum = 0;

		// 確保する定数バッファのサイズを計算
		S32 bufferSize = 0;
		for (U32 i = 0; i < 32; i++)
		{
			S32 monoBufferSize = gpipeline->GetConstantBufferSize(i);
			if (monoBufferSize <= 0 || (mask & (1 << i)) == 0)
			{
				m_StartOffsets.push_back(-1);
			}
			else
			{
				m_StartOffsets.push_back(bufferSize);
				bufferSize += monoBufferSize;
				m_DescriptorNum++;
			}
		}

		m_Data.resize(bufferSize);


		// テクスチャの枚数
		const S32 texNum = gpipeline->GetTextureNum();

		// テクスチャ領域の確保
		m_TextureList.resize(texNum);
		m_TextureListBuffer.resize(texNum);


		if (CreateResource(device, gpipeline) == -1)
		{
			return;
		}

		m_GraphicPipeline = gpipeline;
	}

	S32 Material::CreateResource(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline)
	{
		S32 size = m_Data.size();
		if (size == 0)return 0;

		auto result = device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(size),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_Resource.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;

		Byte* ptr = nullptr;
		result = m_Resource->Map(0, nullptr, (void**)(&ptr));

		std::copy(m_Data.begin(), m_Data.end(), ptr);
		return 0;
	}

	S32 Material::CreateDescriptorHeap(ComPtr<ID3D12Device>& device)
	{
		D3D12_DESCRIPTOR_HEAP_DESC materialDescHeapDesc = {};
		materialDescHeapDesc.NumDescriptors = m_DescriptorNum + (UINT)m_TextureList.size();//定数バッファ + テクスチャ
		materialDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		materialDescHeapDesc.NodeMask = 0;
		materialDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別


		if (materialDescHeapDesc.NumDescriptors == 0)return 0;

		auto result = device->CreateDescriptorHeap(&materialDescHeapDesc, IID_PPV_ARGS(m_DescHeap.ReleaseAndGetAddressOf()));//生成
		if (FAILED(result))return -1;

		auto descHeapH = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
		auto incSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		// 定数
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_Resource->GetGPUVirtualAddress();

		for (U32 i = 0; i < m_StartOffsets.size(); i++)
		{
			if (m_StartOffsets[i] == -1)continue;

			cbvDesc.SizeInBytes = m_GraphicPipeline->GetConstantBufferSize(i);

			device->CreateConstantBufferView(&cbvDesc, descHeapH);
			descHeapH.ptr += incSize;
			cbvDesc.BufferLocation += cbvDesc.SizeInBytes;
		}
		// テクスチャ
		for (auto& tex : m_TextureList)
		{
			if (tex == nullptr)
			{
				tex = DefaultAsset::Instance()->whiteTex;
			}
			tex->CreateShaderResourceView(device, descHeapH);
		}
		return 0;
	}


	S32 Material::SetMaterial(ComPtr<ID3D12Device>& device, ComPtr<ID3D12GraphicsCommandList>& commandList)
	{
		if (!IsValid())return -1;
		if (CheckArgs(device, commandList))return -1;

		if (m_IsChanged)
		{
			CreateDescriptorHeap(device);
			m_IsChanged = false;
		}

		// ディスクリプタを必要としないシェーダーの場合
		if (m_DescHeap == nullptr)return 0;

		ID3D12DescriptorHeap* heaps[] = { m_DescHeap.Get() };
		commandList->SetDescriptorHeaps(1, heaps);


		auto heap = m_DescHeap->GetGPUDescriptorHandleForHeapStart();

		auto incSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		for (U32 i = 0; i < m_StartOffsets.size(); i++)
		{
			if (m_StartOffsets[i] == -1)continue;

			commandList->SetGraphicsRootDescriptorTable(i, heap);
			heap.ptr += incSize;
		}

		// テクスチャの指定
		if (m_TextureList.size() != 0)
		{
			commandList->SetGraphicsRootDescriptorTable(m_DescriptorNum, heap);
		}
		return 0;
	}

	S32 Material::Lock()
	{
		if (!IsValid())return -1;
		// TODO 定数バッファのロック処理
		return 0;
	}



	S32 Material::SetTexture(const String& name, SPtr<Texture>& texture)
	{
		if (!IsValid())return -1;
		if (CheckArgs(!!texture))return -1;

		auto varData = m_GraphicPipeline->GetVariableData(name);

		if (varData.type != ShaderParamType::TEXTURE2D &&
			varData.type != ShaderParamType::TEXTURE3D)
		{
			return -1;
		}

		m_TextureListBuffer[varData.registerNum] = texture;
		m_IsChanged = true;
		return 0;
	}

	S32 Material::SetFloat4Param(const String& name, const Vector4& value)
	{
		if (!IsValid())return -1;

		auto varData = m_GraphicPipeline->GetVariableData(name);

		if (varData.type != ShaderParamType::FLOAT4)
		{
			return -1;
		}

		Byte* bytePtr = m_Data.data() + m_StartOffsets[varData.registerNum] + varData.offset;
		auto ptr = reinterpret_cast<Vector4*>(bytePtr);
		*ptr = value;
		return 0;
	}
}