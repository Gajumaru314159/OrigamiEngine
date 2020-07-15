#pragma once
#include "IRenderTexture.h"
#include "Texture.h"

#include <d3d12.h>

#include "DXHelper.h"

namespace og
{
	class RenderTexture :public IRenderTexture, public Texture
	{
	private:
		ComPtr<ID3D12Resource> m_Depth = nullptr;

		// Write
		ComPtr<ID3D12DescriptorHeap> m_RTVHeap = nullptr;
		// Depth
		ComPtr<ID3D12DescriptorHeap> m_DSVHeap = nullptr;

		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;

		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;


		D3D12_VIEWPORT m_Viewport;         //ビューポート
		D3D12_RECT m_Scissorrect;          //シザー矩形

	public:
		RenderTexture(const DXGI_FORMAT format, const U32 width, const U32 height);


		ID3D12GraphicsCommandList* GetCommandList();

		void ResetCommand();



		S32 BeginDraw()override;
		S32 EndDraw()override;

		S32 SetGraphicPipeline(SPtr<IGraphicPipeline> pipeline)override;

		S32 SetMaterial(SPtr<IMaterial> material)override;

		S32 DrawInstanced(SPtr<IShape>& shape, const U32 count = 1)override;


		Vector3 GetSize()override;
		S32 GetDimension()override;
	};
}