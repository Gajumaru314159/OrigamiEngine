#include "pch.h"

#include "DX12Wrapper.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

//#pragma warning(diable: 4099 )
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_x64_Debug.lib")
#else
#pragma comment(lib, "DirectXTex_x64_Release.lib")
#endif


#include "InnerGraphicPipelineDesc.h"
#include "DefaultAsset.h"

#include "Shader.h"
#include<DirectXMath.h>
namespace
{
	LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_DESTROY)
		{
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}


namespace og
{
	S32 DX12Wrapper::Init()
	{
		//======================================//
		// ウィンドウの生成
		//======================================//

		if (FAILED(CreateMainWindow()))
		{
			return -1;
		}

		//======================================//
		// DirectXの初期化
		//======================================//

		// デバイスの初期化
		if (FAILED(InitializeDXGIDevice()))
		{
			return -1;
		}
		// コマンドキューの初期化
		if (FAILED(InitializeCommand()))
		{
			return -1;
		}
		// スワップチェーンの作成
		if (FAILED(CreateSwapChain(m_Hwnd)))
		{
			return -1;
		}
		// 最終レンダリング先の作成
		if (FAILED(CreateFinalRenderTargets()))
		{
			return -1;
		}
		//フェンスの作成
		if (FAILED(CreateFence()))
		{
			return -1;
		}

		ShowWindow(m_Hwnd, SW_SHOW);

		// デフォルトアセットの作成
		if (CreateDefaultAssets() == -1)
		{
			return -1;
		}

		//Test();
		return 0;
	}

	S32 DX12Wrapper::SwapScreen()
	{
		auto bbIdx = m_Swapchain->GetCurrentBackBufferIndex();
		m_CmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_BackBuffers[bbIdx].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		//命令のクローズ
		m_CmdList->Close();

		//コマンドリストの実行
		ID3D12CommandList* cmdlists[] = { m_CmdList.Get() };
		m_CmdQueue->ExecuteCommandLists(1, cmdlists);
		////待ち
		m_CmdQueue->Signal(m_Fence.Get(), ++m_FenceVal);

		if (m_Fence->GetCompletedValue() < m_FenceVal)
		{
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_Fence->SetEventOnCompletion(m_FenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
		m_CmdAllocator->Reset();                          //キューをクリア
		m_CmdList->Reset(m_CmdAllocator.Get(), nullptr);  //再びコマンドリストをためる準備

		m_Swapchain->Present(1, 0);

		MSG msg = {};
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//もうアプリケーションが終わるって時にmessageがWM_QUITになる
		if (msg.message == WM_QUIT)
		{
			return -1;
		}

		//DirectX処理
		//バックバッファのインデックスを取得
		bbIdx = m_Swapchain->GetCurrentBackBufferIndex();

		m_CmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_BackBuffers[bbIdx].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		//レンダーターゲットを指定
		auto rtvH = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += (SIZE_T)bbIdx * m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * bbIdx;

		//深度を指定
		//auto dsvH = m_DSVHeap->GetCPUDescriptorHandleForHeapStart();
		//m_CmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
		m_CmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);
		//m_CmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		//画面クリア
		float clearColor[] = { 1,1,1,1 };  //白色
		m_CmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

		//ビューポート、シザー矩形のセット
		m_CmdList->RSSetViewports(1, &m_Viewport);
		m_CmdList->RSSetScissorRects(1, &m_Scissorrect);


		m_CmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return 0;
	}

	// ここからprivate関数

	HRESULT DX12Wrapper::CreateMainWindow()
	{
		// ウィンドウクラス生成＆登録
		WNDCLASSEX w = {};
		w.cbSize = sizeof(WNDCLASSEX);
		w.lpfnWndProc = (WNDPROC)WindowProcedure;
		w.lpszClassName = L"DX12Sample";
		w.hInstance = GetModuleHandle(nullptr);

		RegisterClassEx(&w);

		// ウィンドウサイズ
		windowWidth = 1280;
		windowHeight = 720;
		RECT wrc = { 0, 0, windowWidth, windowHeight };

		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

		// ウィンドウオブジェクトの生成
		m_Hwnd = CreateWindow(
			w.lpszClassName,       // クラス名
			L"DX12テスト",    // ウィンドウタイトル
			WS_OVERLAPPEDWINDOW,   // ウィンドウスタイル
			CW_USEDEFAULT,         // X
			CW_USEDEFAULT,         // Y
			wrc.right - wrc.left,  // W
			wrc.bottom - wrc.top,  // H
			nullptr,               // 親ウィンドウ
			nullptr,               // メニューハンドル
			w.hInstance,           // 追加パラメータ
			nullptr);
		return S_OK;
	}

	HRESULT DX12Wrapper::InitializeDXGIDevice()
	{
		UINT flagsDXGI = 0;
		flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
		auto result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return result;
		}

		// アダプターの列挙し、メモリ量が最大のグラフィックボードを選択
		std::vector<IDXGIAdapter*> adapters;

		IDXGIAdapter* tmpAdapter = nullptr;
		IDXGIAdapter* selectedAdapter = nullptr;
		SIZE_T maxVideoCardMemory = 0;
		for (int i = 0; m_DxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
		{
			DXGI_ADAPTER_DESC adesc = {};
			tmpAdapter->GetDesc(&adesc);

			SIZE_T videoCardMemory = (SIZE_T)(adesc.DedicatedVideoMemory / 1024 / 1024);  //(MB)

			if (maxVideoCardMemory < videoCardMemory)
			{
				selectedAdapter = tmpAdapter;
				maxVideoCardMemory = videoCardMemory;
			}
		}

		// 対応しているレベルで生成
		D3D_FEATURE_LEVEL featureLevel;
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		result = S_FALSE;
		for (auto level : levels)
		{
			if (SUCCEEDED(D3D12CreateDevice(selectedAdapter, level, IID_PPV_ARGS(m_Dev.ReleaseAndGetAddressOf()))))
			{
				featureLevel = level;
				result = S_OK;
				break;
			}
		}
		return result;
	}

	HRESULT DX12Wrapper::InitializeCommand()
	{
		auto result = m_Dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_CmdAllocator.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return result;
		}
		result = m_Dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CmdAllocator.Get(), nullptr, IID_PPV_ARGS(m_CmdList.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return result;
		}

		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;       // コマンドリストと合わせる
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;        // タイムアウトなし
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // コマンドキューの優先度
		cmdQueueDesc.NodeMask = 0;                                    // GPUが1つの時は0、複数の時は識別用のbitを指定

		result = m_Dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_CmdQueue.ReleaseAndGetAddressOf()));  //コマンドキュー生成

		return result;
	}

	HRESULT DX12Wrapper::CreateSwapChain(const HWND& hwnd)
	{
		RECT rc = {};
		GetWindowRect(hwnd, &rc);

		DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
		swapchainDesc.Width = rc.right - rc.left;                      // 画面解像度【横】
		swapchainDesc.Height = rc.bottom - rc.top;                      // 画面解像度【縦】
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;              // ピクセルフォーマット
		swapchainDesc.Stereo = false;                                   // 3Dディスプレイかどうか
		swapchainDesc.SampleDesc.Count = 1;                                       // マルチサンプル指定
		swapchainDesc.SampleDesc.Quality = 0;                                       // マルチサンプル指定
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;                  // CPUのバックバッファへのアクセス方法
		swapchainDesc.BufferCount = 2;                                       // バッファの数。ダブルバッファのため2。
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;                    // リサイズ時の挙動。見た目に合わせる。
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;           // スワップ後に速やかに破棄
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;             // バックバッファの透過の挙動
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;  // ウィンドウ⇔フルスクリーン切り替え可能

		auto result = m_DxgiFactory->CreateSwapChainForHwnd(
			m_CmdQueue.Get(),
			hwnd,
			&swapchainDesc,
			nullptr,  // フルスクリーン時の設定
			nullptr,  // アウトプット
			(IDXGISwapChain1**)m_Swapchain.ReleaseAndGetAddressOf());
		return result;
	}

	HRESULT DX12Wrapper::CreateFinalRenderTargets()
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;   // レンダーターゲットビュー
		heapDesc.NodeMask = 0;                                // GPUが1つの時は0、複数の時は識別用のbitを指定
		heapDesc.NumDescriptors = 2;                                // ディスクリプタの数。表と裏バッファの２つ。
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;  // ビューの情報をシェーダから参照する必要があるか

		auto result = m_Dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_RtvHeaps.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return result;
		}


		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		result = m_Swapchain->GetDesc(&swcDesc);
		m_BackBuffers.resize(swcDesc.BufferCount);
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();

		//SRGBレンダーターゲットビュー設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;


		for (U32 i = 0; i < swcDesc.BufferCount; ++i)
		{
			result = m_Swapchain->GetBuffer(i, IID_PPV_ARGS(m_BackBuffers[i].ReleaseAndGetAddressOf()));
			m_Dev->CreateRenderTargetView(m_BackBuffers[i].Get(), &rtvDesc, handle);
			handle.ptr += m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}

		m_Viewport = CD3DX12_VIEWPORT(m_BackBuffers[0].Get());
		m_Scissorrect = CD3DX12_RECT(0, 0, (U32)m_Viewport.Width, (U32)m_Viewport.Height);

		return result;
	}

	HRESULT DX12Wrapper::CreateFence()
	{
		m_FenceVal = 0;
		return m_Dev->CreateFence(m_FenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_Fence.ReleaseAndGetAddressOf()));
	}

	S32 DX12Wrapper::CreateDefaultAssets()
	{
		//DefaultAsset::Instance()->whiteTex = MSPtr<Texture>(m_Dev, 4, 4, ConvertTextureFormat(TextureFormat::RGBA8));
		DefaultAsset::Instance()->whiteTex = MSPtr<Texture>(m_Dev, Path(TC("C:\\My\\Temp\\test.png")));
		if (!DefaultAsset::Instance()->whiteTex->IsValid())return -1;

		{
			String errorDest;

			String vssrc;
			vssrc.append("\ncbuffer Data0 : register(b0) {matrix mat;};");
			vssrc.append("\ncbuffer Data1 : register(b1) {float4 col;};");
			vssrc.append("\nstruct Output {float4 pos:SV_POSITION;float2 uv:TEXCOORD;};");
			vssrc.append("\nOutput VSMain(float4 pos : POSITION ,float2 uv : TEXCOORD) {");
			vssrc.append("\n	 Output o;");
			vssrc.append("\n	 o.pos = mul(transpose(mat),pos);");
			vssrc.append("\n	 o.uv = uv;");
			vssrc.append("\n	 return o;");
			vssrc.append("\n}");
			String pssrc;
			pssrc.append("\nTexture2D<float4> tex:register(t0);");
			pssrc.append("\nSamplerState smp:register(s0);");
			pssrc.append("\ncbuffer Data0 : register(b0) {matrix mat;};");
			pssrc.append("\ncbuffer Data1 : register(b1) {float4 col;};");
			pssrc.append("\nstruct Output {float4 pos:SV_POSITION;float2 uv:TEXCOORD;};");
			pssrc.append("\nfloat4 PSMain(Output i) : SV_TARGET{");
			pssrc.append("\n  return float4(tex.Sample(smp,i.uv))*col;");
			pssrc.append("\n}");

			S32 vs = CreateShader(vssrc, ShaderType::VERTEX, errorDest);
			S32 ps = CreateShader(pssrc, ShaderType::PIXEL, errorDest);
			if (vs == -1 || ps == -1)
			{
				return -1;
			}


			GraphicPipelineDesc pipeline;
			pipeline.vs = vs;
			pipeline.ps = ps;
			pipeline.numRenderTargets = 1;

			S32 id = CreateGraphicPipeline(pipeline);
			if (id == -1)
			{
				return -1;
			}
		}

		m_Vertices[0 * 5 + 0] = 0.0f;
		m_Vertices[0 * 5 + 1] = 0.0f;
		m_Vertices[0 * 5 + 2] = 0.0f;
		m_Vertices[0 * 5 + 3] = 0.0f;
		m_Vertices[0 * 5 + 4] = 0.0f;

		m_Vertices[1 * 5 + 0] = 1.0f;
		m_Vertices[1 * 5 + 1] = 0.0f;
		m_Vertices[1 * 5 + 2] = 0.0f;
		m_Vertices[1 * 5 + 3] = 1.0f;
		m_Vertices[1 * 5 + 4] = 0.0f;

		m_Vertices[2 * 5 + 0] = 0.0f;
		m_Vertices[2 * 5 + 1] = 1.0f;
		m_Vertices[2 * 5 + 2] = 0.0f;
		m_Vertices[2 * 5 + 3] = 0.0f;
		m_Vertices[2 * 5 + 4] = 1.0f;

		m_Vertices[3 * 5 + 0] = 1.0f;
		m_Vertices[3 * 5 + 1] = 1.0f;
		m_Vertices[3 * 5 + 2] = 0.0f;
		m_Vertices[3 * 5 + 3] = 1.0f;
		m_Vertices[3 * 5 + 4] = 1.0f;

		U32 indices[6] = { 0,1,2,2,1,3 };
		m_TexVertID = CreateShape(sizeof(F32) * 5, sizeof(F32) * 5 * 4, (Byte*)m_Vertices, 6, indices);




		return 0;
	}
}