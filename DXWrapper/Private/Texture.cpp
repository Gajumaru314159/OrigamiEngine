#include "pch.h"
#include "Texture.h"

#include "DX12Wrapper.h"

namespace og
{

	S32 Texture::CreateShaderResourceView(D3D12_CPU_DESCRIPTOR_HANDLE& handle)
	{
		if (IsValid() == false)return -1;

		D3D12_SHADER_RESOURCE_VIEW_DESC texDesc = {};
		texDesc.Format = m_resource->GetDesc().Format;
		texDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		texDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		texDesc.Texture2D.MipLevels = 1;

		DX12Wrapper::ms_device->CreateShaderResourceView(m_resource.Get(), &texDesc, handle);

		handle.ptr += DX12Wrapper::ms_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		return 0;
	}


	Vector3 Texture::GetSize()
	{
		// TODO Vector3Intを作る
		if (IsValid() == false)return Vector3();
		auto desc = m_resource->GetDesc();
		return Vector3((F32)desc.Width, (F32)desc.Height, (F32)desc.DepthOrArraySize);
	}

	S32 Texture::GetDimension()
	{
		if (IsValid() == false)return 0;
		auto desc = m_resource->GetDesc();
		return desc.Dimension;
	}

}