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
		:m_cBufferMask(cBufferMask), m_texMask(texMask)
	{
		if (CheckArgs(!!gpipeline))return;
		auto pipelinePtr = reinterpret_cast<GraphicPipeline*>(gpipeline.get());

		m_isChanged = true;
		m_isLocked = false;

		// 確保する定数バッファのサイズを計算
		m_dataSize = 0;
		m_startOffsets.resize(GraphicPipeline::MAX_REGISTER);
		m_targets.resize(GraphicPipeline::MAX_REGISTER);
		for (U32 i = 0; i < GraphicPipeline::MAX_REGISTER; i++)
		{
			S32 monoBufferSize = pipelinePtr->GetConstantBufferSize(i);
			if (monoBufferSize <= 0 || (m_cBufferMask & (1 << i)) == 0)
			{
				m_startOffsets[i] = -1;
			}
			else
			{
				m_resisterIndices.push_back(pipelinePtr->GetConstantBufferIndex(i));
				m_startOffsets[i] = m_dataSize;
				m_dataSize += monoBufferSize;
			}
		}

		S32 texNum = 0;
		m_textureNums.resize(GraphicPipeline::MAX_REGISTER);
		for (U32 i = 0; i < GraphicPipeline::MAX_REGISTER; i++)
		{
			S32 num = pipelinePtr->GetTextureNum(i);
			if (num <= 0 || (m_texMask & (1 << i)) == 0)
			{
				m_textureNums[i] = 0;
			}
			else
			{
				m_resisterIndices.push_back(pipelinePtr->GetTextureIndex(i));
				m_textureNums[i] = num;
				texNum++;
			}
		}


		// テクスチャ領域の確保
		m_textureList.resize(texNum);
		m_textureListBuffer.resize(texNum);


		m_graphicPipeline = gpipeline;


		if (CreateResource() == -1)
		{
			m_graphicPipeline.reset();
			return;
		}
	}



	S32 Material::CreateResource()
	{
		if (m_dataSize == 0)return 0;

		auto result = DX12Wrapper::ms_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(m_dataSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_resource.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;

		result = m_resource->Map(0, nullptr, (void**)(&m_data));
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
		auto result = DX12Wrapper::ms_device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_descHeap.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;


		auto descHeapH = m_descHeap->GetCPUDescriptorHandleForHeapStart();
		auto incrementSize = DX12Wrapper::ms_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		// 定数
		if (m_resource != nullptr)
		{
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = m_resource->GetGPUVirtualAddress();

			for (U32 i = 0; i < m_startOffsets.size(); i++)
			{
				if (m_startOffsets[i] == -1)continue;

				cbvDesc.SizeInBytes = reinterpret_cast<GraphicPipeline*>(m_graphicPipeline.get())->GetConstantBufferSize(i);

				DX12Wrapper::ms_device->CreateConstantBufferView(&cbvDesc, descHeapH);
				descHeapH.ptr += incrementSize;
				cbvDesc.BufferLocation += cbvDesc.SizeInBytes;
			}
		}


		// テクスチャ
		for (S32 i = 0; i < m_textureListBuffer.size(); i++)
		{
			if (m_textureListBuffer[i] == nullptr)continue;
			m_textureList[i] = m_textureListBuffer[i];
			m_textureListBuffer[i].reset();
		}

		for (S32 i = 0; i < m_textureNums.size(); i++)
		{
			if (m_textureNums[i] <= 0)continue;
			if (m_textureList[i] == nullptr)
			{
				m_textureList[i] = DefaultAsset::Instance()->whiteTex;
			}

			auto ptr = dynamic_cast<Texture*>(m_textureList[i].get());
			ptr->CreateShaderResourceView(descHeapH, m_targets[i]);
		}

		return 0;
	}


	S32 Material::SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList)
	{
		if (!IsValid())return -1;
		if (CheckArgs(commandList))return -1;

		// 変更があればでスクリプタヒープの再生成
		if (m_isChanged)
		{
			CreateDescriptorHeap();
			m_isChanged = false;
		}

		// ディスクリプタを必要としないシェーダーの場合
		if (m_descHeap == nullptr)return 0;


		ID3D12DescriptorHeap* heaps[] = { m_descHeap.Get() };
		commandList->SetDescriptorHeaps(1, heaps);


		auto heap = m_descHeap->GetGPUDescriptorHandleForHeapStart();

		auto incSize = DX12Wrapper::ms_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

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



	S32 Material::SetTexture(const String& name, const SPtr<ITexture>& texture, const S32 target)
	{
		if (!IsValid())return -1;
		if (CheckArgs(!!texture))return -1;
		if (m_isLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_graphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::TEXTURE2D &&
			varData.type != ShaderParamType::TEXTURE3D)
		{
			return -1;
		}

		// 変更なしなら何もしない
		if (m_textureList[varData.registerNum] == texture)return 0;
		if (m_textureNums[varData.registerNum] == 0)return -1;

		m_textureListBuffer[varData.registerNum] = texture;
		m_targets[varData.registerNum] = target;
		m_isChanged = true;
		return 0;
	}

	S32 Material::SetFloat4Param(const String& name, const Vector4& value)
	{
		if (!IsValid())return -1;
		if (m_isLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_graphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::FLOAT4)return -1;
		if (m_startOffsets[varData.registerNum] == -1)return -1;

		Byte* bytePtr = m_data + m_startOffsets[varData.registerNum] + varData.offset;
		auto ptr = reinterpret_cast<Vector4*>(bytePtr);
		*ptr = value;
		return 0;
	}

	S32 Material::SetMatrixParam(const String& name, const Matrix& value)
	{
		if (!IsValid())return -1;
		if (m_isLocked)return -1;

		auto varData = reinterpret_cast<GraphicPipeline*>(m_graphicPipeline.get())->GetVariableData(name);

		if (varData.type != ShaderParamType::MATRIX)return -1;
		if (m_startOffsets[varData.registerNum] == -1)return -1;

		Byte* bytePtr = m_data + m_startOffsets[varData.registerNum] + varData.offset;
		auto ptr = reinterpret_cast<Matrix*>(bytePtr);
		*ptr = value;
		return 0;
	}
}