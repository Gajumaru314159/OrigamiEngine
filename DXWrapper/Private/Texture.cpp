#include "pch.h"
#include "Texture.h"

#include "DX12Wrapper.h"

namespace og
{

	S32 Texture::CreateShaderResourceView(D3D12_CPU_DESCRIPTOR_HANDLE& handle, const S32 target)
	{
		if (IsValid() == false)return -1;

		if (0 <= target && target < m_resources.size())
		{
			D3D12_SHADER_RESOURCE_VIEW_DESC texDesc = {};
			texDesc.Format = m_resources[target]->GetDesc().Format;
			texDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			texDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			texDesc.Texture2D.MipLevels = 1;

			DX12Wrapper::ms_device->CreateShaderResourceView(m_resources[target].Get(), &texDesc, handle);
		}

		handle.ptr += DX12Wrapper::ms_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		return 0;
	}


	Vector3 Texture::GetSize()
	{
		// TODO Vector3Intを作る
		if (IsValid() == false)return Vector3();
		auto desc = m_resources[0]->GetDesc();
		return Vector3((F32)desc.Width, (F32)desc.Height, (F32)desc.DepthOrArraySize);
	}

	S32 Texture::GetDimension()
	{
		if (IsValid() == false)return 0;
		auto desc = m_resources[0]->GetDesc();
		return desc.Dimension;
	}




	// ここからプライベート関数
	DXGI_FORMAT Texture::ConvertTextureFormat(const TextureFormat format)const
	{
		switch (format)
		{
		case TextureFormat::RGBA32:		return DXGI_FORMAT_R32G32B32A32_FLOAT;//
		case TextureFormat::RGBA16:		return DXGI_FORMAT_R16G16B16A16_UNORM;
		case TextureFormat::RGBA8:		return DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::RG8:		return DXGI_FORMAT_R8G8_SNORM;
		case TextureFormat::R32:		return DXGI_FORMAT_R32_FLOAT;//
		case TextureFormat::R16:		return DXGI_FORMAT_R16_UNORM;
		case TextureFormat::R8:			return DXGI_FORMAT_R8_UNORM;
		case TextureFormat::Depth:		return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case TextureFormat::RGB565:		return DXGI_FORMAT_B5G6R5_UNORM;
		case TextureFormat::RGBA5551:	return DXGI_FORMAT_B5G5R5A1_UNORM;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

}