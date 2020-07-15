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
			ms_Device->Release();
			ms_Device = nullptr;

		}

#pragma region
		// IGraphicWrapperの仮想関数の実装

		S32 Init() override;
		S32 SwapScreen(SPtr<IRenderTexture>& renderTarget) override;

		//===================================================================================//

		SPtr<IRenderTexture> CreateRenderTexture(const S32 width, const S32 height, const TextureFormat format)override;
		SPtr<ITexture> LoadTexture(const Path& path, const bool async) override;

		//===================================================================================//

		SPtr<IShader> LoadShader(const String& path, ShaderType type, String& errorDest) override;
		SPtr<IShader> CreateShader(const String& path, ShaderType type, String& errorDest) override;

		//===================================================================================//

		SPtr<IGraphicPipeline> CreateGraphicPipeline(const GraphicPipelineDesc& desc)override;

		//===================================================================================//

		SPtr<IMaterial> CreateMaterial(const SPtr<IGraphicPipeline>& pipeline, const S32 mask = -1)override;

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

		DXGI_FORMAT ConvertTextureFormat(const TextureFormat format)const;
	private:
#pragma region
		// ウィンドウ関係
		HWND m_Hwnd;
		LONG windowWidth;
		LONG windowHeight;

		// DXGI関係
		ComPtr<IDXGIFactory4> m_DxgiFactory = nullptr;  // DXGIインターフェイス
		ComPtr<IDXGISwapChain4> m_Swapchain = nullptr;  // スワップチェイン

		// DirectX12関係
		//ComPtr<ID3D12Device> m_Dev = nullptr;  //デバイス
		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;  //コマンドアロケータ
		ComPtr<ID3D12CommandQueue> m_CmdQueue = nullptr;  //コマンドキュー
		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;  //コマンドリスト

		// 表示に関わるバッファ関係
		ArrayList<ComPtr<ID3D12Resource>> m_BackBuffers;         //バックバッファ(2つ以上…スワップチェインが確保)
		ComPtr<ID3D12DescriptorHeap> m_RtvHeaps = nullptr;  //レンダーターゲット用デスクリプタヒープ
		D3D12_VIEWPORT m_Viewport;         //ビューポート
		D3D12_RECT m_Scissorrect;          //シザー矩形

		// フェンス
		ComPtr<ID3D12Fence> m_Fence = nullptr;
		UINT64 m_FenceVal = 0;


		// 描画用リソース
		SPtr<IGraphicPipeline> m_graphicPipeline;
		SPtr<IShape> m_shape;
		SPtr<IMaterial> m_material;
	public:
		static ID3D12Device* ms_Device;
		static ArrayList<IRenderTexture*> ms_RenderTextureQueue;

#pragma endregion
	};
}