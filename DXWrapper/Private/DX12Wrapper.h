#pragma once

#include "IDXWrapper.h"

#include <functional>

#include <d3d12.h>
#include<dxgi1_6.h>
#include<d3dx12.h>

#include <DirectXTex.h>
#ifdef _DEBUG
#pragma comment(lib,"DirectXTex_x64_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_x64_Release.lib")
#endif


#include <wrl.h>

namespace OrigamiGraphic
{
	class DX12Wrapper :public IDXWrapper
	{
	public:
		int Init()override;

		int SwapScreen()override;

		int LoadGraph(const String& path)override;

	private:
		// ウィンドウ回り
		HWND m_Hwnd;
		LONG windowWidth;
		LONG windowHeight;

		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		// DXGIまわり
		ComPtr<IDXGIFactory4> m_DxgiFactory = nullptr;	// DXGIインターフェイス
		ComPtr<IDXGISwapChain4> m_Swapchain = nullptr;	// スワップチェイン

		// DirectX12まわり
		ComPtr<ID3D12Device> m_Dev = nullptr;//デバイス
		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;//コマンドアロケータ
		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;//コマンドリスト
		ComPtr<ID3D12CommandQueue> m_CmdQueue = nullptr;//コマンドキュー

		// 表示に関わるバッファ周り
		std::vector<ID3D12Resource*> m_BackBuffers;	//バックバッファ(2つ以上…スワップチェインが確保)
		ComPtr<ID3D12DescriptorHeap> m_RtvHeaps = nullptr;//レンダーターゲット用デスクリプタヒープ
		std::unique_ptr<D3D12_VIEWPORT> m_Viewport;//ビューポート
		std::unique_ptr<D3D12_RECT> m_Scissorrect;//シザー矩形

		// フェンス
		ComPtr<ID3D12Fence> m_Fence = nullptr;
		UINT64 m_FenceVal = 0;

		// テクスチャロードテーブル
		using LoadLambda_t = std::function<HRESULT(const String & path, DirectX::TexMetadata*, DirectX::ScratchImage&)>;
		HashMap < String, LoadLambda_t> m_LoadLambdaTable;

		ArrayList<ComPtr<ID3D12Resource>> m_TextureMap;


		HRESULT CreateMainWindow();
		HRESULT InitializeDXGIDevice();
		HRESULT InitializeCommand();
		HRESULT CreateSwapChain(const HWND& hwnd);
		HRESULT CreateFinalRenderTargets();
		HRESULT CreateSceneView();
		HRESULT CreateFence();


		void CreateTextureLoaderTable();
	};
}