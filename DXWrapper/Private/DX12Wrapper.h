#pragma once

#include "IGraphicWrapper.h"

#include <functional>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

#include "DefaultAsset.h"
#include "DXHelper.h"


namespace og
{
	class DX12Wrapper : public IGraphicWrapper, public Singleton<DX12Wrapper>
	{
		friend class Singleton<DX12Wrapper>;
	public:
		~DX12Wrapper()
		{
			DefaultAsset::ResetSingleton();
			ms_device->Release();
			ms_device = nullptr;

		}

#pragma region
		// IGraphicWrapperの仮想関数の実装

		S32 Init() override;
		S32 SwapScreen(SPtr<IRenderTexture>& renderTarget) override;

		//===================================================================================//

		SPtr<IRenderTexture> CreateRenderTexture(const S32 width, const S32 height, const TextureFormat format)override;
		SPtr<IRenderTexture> CreateRenderTexture(const S32 width, const S32 height, const ArrayList<TextureFormat>& formats)override;
		SPtr<ITexture> LoadTexture(const Path& path, const bool async) override;

		//===================================================================================//

		SPtr<IShader> LoadShader(const String& path, ShaderType type, String& errorDest) override;
		SPtr<IShader> CreateShader(const String& path, ShaderType type, String& errorDest) override;

		//===================================================================================//

		SPtr<IGraphicPipeline> CreateGraphicPipeline(const GraphicPipelineDesc& desc)override;

		//===================================================================================//

		SPtr<IMaterial> CreateMaterial(const SPtr<IGraphicPipeline>& pipeline, const S32 cBufferMask, const S32 texMask)override;

		//===================================================================================//

		SPtr<IShape> CreateShape(const U32 stribeSize) override;

		//S32 DrawShape(SPtr<IShape> shape)override;

#pragma endregion
	private:
		// 初期化
		HRESULT CreateMainWindow();
		HRESULT InitializeDXGIDevice();
		HRESULT InitializeCommand();
		HRESULT CreateSwapChain(const HWND& hwnd);
		HRESULT CreateFinalRenderTargets();
		HRESULT CreateFence();
		S32 CreateDefaultAssets();

	private:
#pragma region
		// ウィンドウ関係
		HWND m_hwnd;
		LONG m_windowWidth;
		LONG m_windowHeight;

		// DXGI関係
		ComPtr<IDXGIFactory4> m_dxgiFactory = nullptr;  // DXGIインターフェイス
		ComPtr<IDXGISwapChain4> m_swapchain = nullptr;  // スワップチェイン

		// DirectX12関係
		//ComPtr<ID3D12Device> m_Dev = nullptr;  //デバイス
		ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;  //コマンドアロケータ
		ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;  //コマンドキュー
		ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;  //コマンドリスト

		// 表示に関わるバッファ関係
		ArrayList<ComPtr<ID3D12Resource>> m_backBuffers;         //バックバッファ(2つ以上…スワップチェインが確保)
		ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;  //レンダーターゲット用デスクリプタヒープ
		D3D12_VIEWPORT m_viewport;         //ビューポート
		D3D12_RECT m_scissorrect;          //シザー矩形

		// フェンス
		ComPtr<ID3D12Fence> m_fence = nullptr;
		UINT64 m_fenceVal = 0;


		// 描画用リソース
		SPtr<IGraphicPipeline> m_graphicPipeline;
		SPtr<IShape> m_shape;
		SPtr<IMaterial> m_material;
	public:
		static ID3D12Device* ms_device;
		static ArrayList<IRenderTexture*> ms_renderTextureQueue;

#pragma endregion
	};
}