#pragma once

#include "IGraphicWrapper.h"

#include <functional>
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

#include "DefaultAsset.h"


namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace og
{
	//class Texture;
	class Shader;
	class GraphicPipeline;
	//class Material;
	class Shape;



	class DX12Wrapper : public IGraphicWrapper
	{
	public:
		~DX12Wrapper()
		{
			DefaultAsset::ResetSingleton();
		}

		#pragma region
		// IGraphicWrapperの仮想関数の実装

		S32 Init() override;
		S32 SwapScreen() override;

		//===================================================================================//

		SPtr<IRenderTexture> CreateRenderTexture(const S32 width, const S32 height, const TextureFormat format)override;
		SPtr<ITexture> LoadTexture(const Path& path, const bool async) override;

		//===================================================================================//

		S32 LoadShader(const String& path, ShaderType type, String& errorDest) override;
		S32 CreateShader(const String& path, ShaderType type, String& errorDest) override;
		S32 DeleteShader(const S32 id)override;

		//===================================================================================//

		S32 CreateGraphicPipeline(const GraphicPipelineDesc& desc)override;
		S32 DeleteGraphicPipeline(const S32 id) override;
		S32 SetGraphicPipeline(const S32 id) override;
		const HashMap<String, ShaderVariableDesc>& GetShaderParamList(const S32 graphicPipelineID)override;

		//===================================================================================//


		SPtr<IMaterial> CreateMaterial(const S32 id, const S32 mask)override;
		S32 SetMaterial(SPtr<IMaterial> material) override;


		//===================================================================================//

		S32 CreateShape(const U32 stribeSize, const U32 dataSize, const Byte* data, const U32 indexNum = 0, const U32* indicis = nullptr) override;


		S32 DrawShape(const S32 id)override;

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
		ComPtr<ID3D12Device> m_Dev = nullptr;  //デバイス
		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;  //コマンドアロケータ
		ComPtr<ID3D12CommandQueue> m_CmdQueue = nullptr;  //コマンドキュー

		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;  //コマンドリスト

		// 表示に関わるバッファ関係
		ArrayList<ComPtr<ID3D12Resource>> m_BackBuffers;         //バックバッファ(2つ以上…スワップチェインが確保)
		ComPtr<ID3D12DescriptorHeap> m_RtvHeaps = nullptr;  //レンダーターゲット用デスクリプタヒープ
		D3D12_VIEWPORT m_Viewport;         //ビューポート
		D3D12_RECT m_Scissorrect;          //シザー矩形


		//ComPtr<ID3D12Resource> m_Depth;

		// フェンス
		ComPtr<ID3D12Fence> m_Fence = nullptr;
		UINT64 m_FenceVal = 0;


		// リソース管理関係

		ArrayList<SPtr<Shader>> m_ShaderList;
		ArrayList<SPtr<GraphicPipeline>> m_PipelineList;
		//ArrayList<SPtr<Material>> m_MaterialList;
		//ArrayList<SPtr<Texture>> m_TextureList;
		ArrayList<SPtr<Shape>> m_ShapeList;


		// 画像描画用頂点データ
		float m_Vertices[4 * (4 + 2)];
		S32 m_TexVertID;
		#pragma endregion
	};
}