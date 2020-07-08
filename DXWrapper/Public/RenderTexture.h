#pragma once
#include "IRenderTexture.h"

#include <d3d12.h>

#include "DXHelper.h"

namespace og
{
	class RenderTexture :public IRenderTexture
	{
	private:
		ComPtr<ID3D12Resource> m_Resource = nullptr;
		ComPtr<ID3D12DescriptorHeap> m_RTVHeap = nullptr;
		ComPtr<ID3D12DescriptorHeap> m_SRVHeap = nullptr;

		ComPtr<ID3D12GraphicsCommandList> m_ComList = nullptr;
	public:
		RenderTexture(ComPtr<ID3D12Device>& device, const DXGI_FORMAT format, const U32 width, const U32 height);

		S32 DrawInstanced(SPtr<IShape>& shape, const U32 count)override;
		Vector3 GetSize()override;
		S32 GetDimension()override;

		inline bool IsValid()const { return m_Resource != nullptr; }
	};
}