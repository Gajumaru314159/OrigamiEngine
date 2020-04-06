#pragma once

#include "IDXWrapper.h"

#include <functional>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

#include <DirectXTex.h>
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_x64_Debug.lib")
#else
#pragma comment(lib, "DirectXTex_x64_Release.lib")
#endif

#include <wrl.h>

#include "Material.h"

namespace OrigamiGraphic
{


	class DX12Wrapper : public IDXWrapper
	{
	public:
		#pragma region
		// 関数の説明はIDXWrapperを参照

		S32 Init() override;

		S32 SwapScreen() override;

		S32 LoadGraph(const String& path) override;



		S32 LoadShader(const String& path, ShaderType type, String& errorDest) override;
		S32 DeleteShader(const S32 id)override;


		S32 CreateGraphicPipeline(const PipelineDesc& desc)override;
		S32 DeleteGraphicPipeline(const S32 id) override;



		S32 CreateMaterial(const S32 id)override;
		S32 DeleteMaterial(const S32 id) override;

		S32 SetMaterial(const S32 id)override;

		S32 SetMaterialFloatParam(const String& name, const F32 value)override;


		S32 CreateTexture(S32 width, S32 height, TextureFormat format)override;
		#pragma endregion
	private:
		// 初期化
		HRESULT CreateMainWindow();
		HRESULT InitializeDXGIDevice();
		HRESULT InitializeCommand();
		HRESULT CreateSwapChain(const HWND& hwnd);
		HRESULT CreateFinalRenderTargets();
		HRESULT CreateSceneView();
		HRESULT CreateFence();
		void CreateTextureLoaderTable();
		HRESULT CreateDefaultAssets();

		bool IsCompiledShader(const String& path);
		S32 GetShaderDataSize(ShaderParamType type);
		S32 GetTextureFormatSize(const TextureFormat format)const;
		DXGI_FORMAT ConvertTextureFormat(const TextureFormat format)const;

	private:
		#pragma region
		// ウィンドウ関係
		HWND m_Hwnd;
		LONG windowWidth;
		LONG windowHeight;

		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		// DXGI関係
		ComPtr<IDXGIFactory4> m_DxgiFactory = nullptr;  // DXGIインターフェイス
		ComPtr<IDXGISwapChain4> m_Swapchain = nullptr;  // スワップチェイン

		// DirectX12関係
		ComPtr<ID3D12Device> m_Dev = nullptr;  //デバイス
		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;  //コマンドアロケータ
		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;  //コマンドリスト
		ComPtr<ID3D12CommandQueue> m_CmdQueue = nullptr;  //コマンドキュー

		// 表示に関わるバッファ関係
		ArrayList<ID3D12Resource*> m_BackBuffers;         //バックバッファ(2つ以上…スワップチェインが確保)
		ComPtr<ID3D12DescriptorHeap> m_RtvHeaps = nullptr;  //レンダーターゲット用デスクリプタヒープ
		UPtr<D3D12_VIEWPORT> m_Viewport;         //ビューポート
		UPtr<D3D12_RECT> m_Scissorrect;          //シザー矩形

		// フェンス
		ComPtr<ID3D12Fence> m_Fence = nullptr;
		UINT64 m_FenceVal = 0;


		// テクスチャ読み込み関係
		using LoadLambdaFunc = std::function<HRESULT(const String & path, DirectX::TexMetadata*, DirectX::ScratchImage&)>;
		HashMap<String, LoadLambdaFunc> m_LoadLambdaTable;




		// リソース管理関係
		struct PipelineSet
		{
			PipelineDesc desc;
			ComPtr<ID3D12PipelineState> pipelineState;
			ComPtr<ID3D12RootSignature> rootSignature;
			S32 referenceCount = 0;
		};

		ArrayList<ComPtr<ID3DBlob>> m_ShaderList;
		ArrayList<PipelineSet> m_PipelineList;
		ArrayList<SPtr<Material>> m_MaterialList;
		ArrayList<ComPtr<ID3D12Resource>> m_TextureList;

		S32 m_CurrentMaterialID;

		// デフォルトアセット
		S32 m_whiteTexID;


		#pragma endregion
	};
}  // namespace OrigamiGraphic