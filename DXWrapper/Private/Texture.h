#pragma once
#include "ITexture.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	class Texture :public ITexture
	{
	protected:
		ArrayList<ComPtr<ID3D12Resource>> m_resources;
		ComPtr<ID3D12DescriptorHeap> m_srvHeap;
	public:

		S32 CreateShaderResourceView(D3D12_CPU_DESCRIPTOR_HANDLE& handle, const S32 target = 0);

		inline bool IsValid()const { return m_resources.empty() == false; }


		virtual Vector3 GetSize()override;
		virtual S32 GetDimension()override;


		DXGI_FORMAT ConvertTextureFormat(const TextureFormat format)const;
	};
}