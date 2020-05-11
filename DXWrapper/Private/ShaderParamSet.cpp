#include "pch.h"
#include "ShaderParamSet.h"

#include <d3dx12.h>
#include "GraphicPipeline.h"
#include "Shader.h"
#include "DefaultAsset.h"

namespace og
{
	ShaderParamSet::ShaderParamSet(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline, const S32 index)
	{
		if (CheckArgs(device, !!gpipeline))return;

		// シェーダパラメータのサイズ
		const S32 shaderParamSize = gpipeline->GetDataSize(index);
		if (shaderParamSize < 0)return;

		// シェーダーパラメータ領域の確保
		m_Data.resize(shaderParamSize);


		// テクスチャの枚数
		const S32 texNum = gpipeline->GetTextureNum(index);
		if (texNum < 0)return;

		// テクスチャ領域の確保
		m_TextureList.resize(texNum);
		m_TextureListBuffer.resize(texNum);

		if (ApplyTextures(device) == -1)
		{
			return;
		}

		m_GraphicPipeline = gpipeline;
		m_Index = index;
	}


	S32 ShaderParamSet::ApplyTextures(ComPtr<ID3D12Device>& device)
	{
		if (!IsValid())return-1;
		if (CheckArgs(device))return -1;

		// シェーダパラメータのサイズ
		const S32 shaderParamSize = m_GraphicPipeline->GetDataSize(m_Index);
		// テクスチャの枚数
		const S32 texNum = m_GraphicPipeline->GetTextureNum(m_Index);

		// ディスクリプタヒープ
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.NumDescriptors = ((0 < shaderParamSize) ? 1 : 0) + texNum;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別

		ComPtr<ID3D12DescriptorHeap> descHeap;

		auto result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(descHeap.ReleaseAndGetAddressOf()));
		if (FAILED(result))return -1;


		auto descHeapH = descHeap->GetCPUDescriptorHandleForHeapStart();


		//======================================//
		// シェーダパラメータ
		//======================================//

		// シェーダパラメータをGPUに確保
		if (0 < shaderParamSize)
		{
			result = device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer((shaderParamSize + 0xff) & ~0xff),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(m_ShaderParamResource.ReleaseAndGetAddressOf())
			);
			// マップ
			result = m_ShaderParamResource->Map(0, nullptr, (void**)m_Data.data());//マップ
			if (FAILED(result))return -1;

			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = m_ShaderParamResource->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = (UINT)(m_ShaderParamResource->GetDesc().Width);

			//定数バッファビューの作成
			device->CreateConstantBufferView(&cbvDesc, descHeapH);

			descHeapH.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}

		//======================================//
		// テクスチャ
		//======================================//

		if (0 < texNum)
		{
			//テクスチャのビューを生成
			for (S32 i = 0; i < m_TextureList.size(); i++)
			{
				if (m_TextureListBuffer.at(i))
				{
					m_TextureList.at(i) = m_TextureListBuffer.at(i);
				}
				if (!m_TextureList.at(i))
				{
					m_TextureList.at(i) = DefaultAsset::Instance()->whiteTex;
				}
				if (!m_TextureList.at(i))return 0;
				m_TextureList.at(i)->CreateShaderResourceView(device, descHeapH);
			}
		}


		m_DescHeap = descHeap;
		return 0;
	}



	S32 ShaderParamSet::SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList)
	{
		if (!IsValid())return -1;
		if (CheckArgs(commandList))return -1;

		ID3D12DescriptorHeap* heaps[] = { m_DescHeap.Get() };
		commandList->SetDescriptorHeaps(1, heaps);
		// ルートパラメータとディスクリプタの関連づけ
		commandList->SetGraphicsRootDescriptorTable(m_Index, m_DescHeap->GetGPUDescriptorHandleForHeapStart());
		return 0;
	}


	S32 ShaderParamSet::SetTexture(const String& name, SPtr<Texture>& texture)
	{
		if (!IsValid())return -1;
		if (CheckArgs(!!m_GraphicPipeline, !!texture))return -1;

		S32 textureIndex = m_GraphicPipeline->GetTextureIndex(m_Index, name);
		if (textureIndex < 0 || m_TextureListBuffer.size() <= textureIndex)return -1;

		m_TextureListBuffer.at(textureIndex) = texture;
		return 0;
	}



	S32 ShaderParamSet::SetFloat4Param(const String& name, const Vector4& value)
	{
		if (!IsValid())return -1;
		const S32 dataSize = Shader::GetShaderDataSize(ShaderParamType::FLOAT4);
		S32 offset = m_GraphicPipeline->GetDataOffset(m_Index, name);
		if (offset < 0 || m_Data.size() <= offset + dataSize)return -1;
		auto ptr = reinterpret_cast<Vector4*>(m_Data.data() + offset);
		*ptr = value;
		return 0;
	}

}