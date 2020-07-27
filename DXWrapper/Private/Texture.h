#pragma once
#include "ITexture.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	class Texture :public ITexture
	{
	protected:
		ComPtr<ID3D12Resource> m_resource;
		ComPtr<ID3D12DescriptorHeap> m_srvHeap;
	public:

		S32 CreateShaderResourceView(D3D12_CPU_DESCRIPTOR_HANDLE& handle);

		inline bool IsValid()const { return m_resource != nullptr; }


		virtual Vector3 GetSize()override;
		virtual S32 GetDimension()override;
	};
}