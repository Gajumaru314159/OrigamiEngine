#include "pch.h"
#include "Material.h"

#include <d3dx12.h>

#include  "DX12Wrapper.h"

#include "GraphicPipeline.h"
#include "Texture.h"
#include "DefaultAsset.h"

#include<DirectXMath.h>

namespace og
{
	Material::Material(const SPtr<IGraphicPipeline>& gpipeline, const S32 cBufferMask, const S32 texMask) 
		:m_cBufferMask(cBufferMask),m_texMask(texMask)
	{
		if (CheckArgs(!!gpipeline))return;
		auto pipelinePtr = reinterpret_cast<GraphicPipeline*>(gpipeline.get());

		m_IsChanged = true;
		m_IsLocked = false;

		// 確保する定数バッファのサイズを計算
		m_DataSize = 0;
		m_StartOffsets.resize(GraphicPipeline::MAX_REGISTER);
		for (U32 i = 0; i < GraphicPipeline::MAX_REGISTER; i++)
		{
			S32 monoBufferSize = pipelinePtr->GetConstantBufferSize(i);
			if (monoBufferSize <= 0 || (m_cBufferMask & (1 << i)) == 0)
			{
				m_StartOffsets[i]=-1;
			}
			else
			{
				m_resisterIndices.push_back(pipelinePtr->GetConstantBufferIndex(i));
				m_StartOffsets[i]= m_DataSize;
				m_DataSize += monoBufferSize;
			}
		}

		S32 texNum = 0;
		m_TextureNums.resize(GraphicPipeline::MAX_REGISTER);
		for (U32 i = 0; i < GraphicPipeline::MAX_REGISTER; i++)
		{
			S32 num = pipelinePtr->GetTextureNum(i);
			if (num <= 0 || (m_texMask & (1 << i)) == 0)
			{
				m_TextureNums[i] = 0;
			}
			else
			{
				m_resisterIndices.push_back(pipelinePtr->GetTextureIndex(i));
				m_TextureNums[i] = num;
				texNum++;
			}
		}


		// テクスチャ領域の確保
		m_ITextureList.resize(texNum);
		m_ITextureListBuffer.resize(texNum);


		m_GraphicPipeline = gpipeline;


		if (CreateResource() == -1)
		{
			m_GraphicPipeline.reset();
			return;
		}
	}



	S32 Material::CreateResource()
	{
		if (m_DataSize == 0)return 0;

		auto result = DX12Wrapper::ms_Device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(m_DataSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_Resource.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;

		result = m_Resource->Map(0, nullptr, (void**)(&m_Data));
		if (FAILED(result))return -1;
		return 0;
	}



	S32 Material::CreateDescriptorHeap()
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = (UINT)m_resisterIndices.size();//定数バッファ + テクスチャ
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別

		//生成
		auto result = DX12Wrapper::ms_Device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_DescHeap.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;


		auto descHeapH = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
		auto incrementSize = DX12Wrapper::ms_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		// 定数
		if (m_Resource != nullptr)
		{
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = m_Resource->GetGPUVirtualAddress();

			for (U32 i = 0; i < m_StartOffsets.size(); i++)
			{
				if (m_StartOffsets[i] == -1)continue;

				cbvDesc.SizeInBytes = reinterpret_cast<GraphicPipeline*>(m_GraphicPipeline.get())->GetConstantBufferSize(i);

				DX12Wrapper::ms_Device->CreateConstantBufferView(&cbvDesc, descHeapH);
				descHeapH.ptr += incrementSize;
				cbvDesc.BufferLocation += cbvDesc.SizeInBytes;
			}
		}


		// テクスチャ
		for (S32 i = 0; i < m_ITextureListBuffer.size(); i++)
		{
			if (m_ITextureListBuffer[i] == nullptr)continue;
			m_ITextureList[i] = m_ITextureListBuffer[i];
			m_ITextureListBuffer[i].reset();
		}

		for (S32 i = 0; i < m_TextureNums.size(); i++)
		{
			if (m_TextureNums[i] <= 0)continue;
			if (m_ITextureList[i] == nullptr)
			{
				m_ITextureList[i] = DefaultAsset::Instance()->whiteTex;
			}

			auto ptr = dynamic_cast<Texture*>(m_ITextureList[i].get());
			ptr->CreateShaderResourceView(descHeapH);
		}

		return 0;
	}


	S32 Material::SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList)
	{
		if (!IsValid())return -1;
		if (CheckArgs(commandList))return -1;

		// 変更があればでスクリプタヒープの再生成
		if (m_IsChanged)
		{
			CreateDescriptorHeap();
			m_IsChanged = false;
		}

		// ディスクリプタを必要としないシェーダーの場合
		if (m_DescHeap == nullptr)return 0;


		ID3D12DescriptorHeap* heaps[] = { m_DescHeap.Get() };
		commandList->SetDescriptorHeaps(1, heaps);


		auto heap = m_DescHeap->GetGPUDescriptorHandleForHeapStart();

		auto incSize = DX12Wrapper::ms_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		for (auto& index : m_resisterIndices)
		{
			commandList->SetGraphicsRootDescriptorTable(index, heap);
			heap.ptr += incSize;
		}

		return 0;
	}

	S32 Material::Lock()
	{
		if (!IsValid())return -1;
		// TODO 定数バッファのロック処理
		return 0;
	}



	S32 Material::SetTexture(const String& name, const SPtr<ITexture>& texture)
	{
		if (!IsValid())return -1;
		if (CheckArgs(!!texture))return -1;
		if (m_IsLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_GraphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::TEXTURE2D &&
			varData.type != ShaderParamType::TEXTURE3D)
		{
			return -1;
		}

		// 変更なしなら何もしない
		if (m_ITextureList[varData.registerNum]==texture)return 0;
		if (m_TextureNums[varData.registerNum]==0)return -1;

		m_ITextureListBuffer[varData.registerNum] = texture;
		m_IsChanged = true;
		return 0;
	}

	S32 Material::SetFloat4Param(const String& name, const Vector4& value)
	{
		if (!IsValid())return -1;
		if (m_IsLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_GraphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::FLOAT4)return -1;
		if (m_StartOffsets[varData.registerNum] == -1)return -1;

		Byte* bytePtr = m_Data + m_StartOffsets[varData.registerNum] + varData.offset;
		auto ptr = reinterpret_cast<Vector4*>(bytePtr);
		*ptr = value;
		return 0;
	}

	S32 Material::SetMatrixParam(const String& name, const Matrix& value)
	{
		if (!IsValid())return -1;
		if (m_IsLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_GraphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::MATRIX)return -1;
		if (m_StartOffsets[varData.registerNum] == -1)return -1;

		Byte* bytePtr = m_Data + m_StartOffsets[varData.registerNum] + varData.offset;
		auto ptr = reinterpret_cast<Matrix*>(bytePtr);
		*ptr = value;
		return 0;
	}
}