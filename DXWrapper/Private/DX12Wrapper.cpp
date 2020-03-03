#include"pch.h"

#include"DX12Wrapper.h"

#include<d3d12.h>
#pragma comment(lib, "d3d12.lib")
#include<dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")
#include<d3dx12.h>

#ifdef _DEBUG
#pragma comment(lib,"DirectXTex_x64_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_x64_Release.lib")
#endif

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


namespace OrigamiGraphic
{
	int DX12Wrapper::Init()
	{
		//======================================//
		// ウィンドウの生成
		//======================================//
		
		if (FAILED(CreateMainWindow())) {
			return -1;
		}


		//======================================//
		// DirectXの初期化
		//======================================//

		// デバイスの初期化
		if (FAILED(InitializeDXGIDevice())) {
			return -1;
		}
		// コマンドキューの初期化
		if (FAILED(InitializeCommand())) {
			return -1;
		}
		// スワップチェーンの作成
		if (FAILED(CreateSwapChain(m_Hwnd))) {
			return -1;
		}
		// 最終レンダリング先の作成
		if (FAILED(CreateFinalRenderTargets())) {
			return -1;
		}
		// レンダリングに使用する変換行列の定義
		if (FAILED(CreateSceneView())) {
			return -1;
		}
		//フェンスの作成
		if (FAILED(CreateFence())) {
			return -1;
		}

		// テクスチャロードテーブルの作成
		CreateTextureLoaderTable();

		ShowWindow(m_Hwnd, SW_SHOW);
		return 0;
	}

	int DX12Wrapper::SwapScreen()
	{
		auto bbIdx = m_Swapchain->GetCurrentBackBufferIndex();
		m_CmdList->ResourceBarrier(1,
			&CD3DX12_RESOURCE_BARRIER::Transition(m_BackBuffers[bbIdx],
				D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		//命令のクローズ
		m_CmdList->Close();



		//コマンドリストの実行
		ID3D12CommandList* cmdlists[] = { m_CmdList.Get() };
		m_CmdQueue->ExecuteCommandLists(1, cmdlists);
		////待ち
		m_CmdQueue->Signal(m_Fence.Get(), ++m_FenceVal);

		if (m_Fence->GetCompletedValue() < m_FenceVal) {
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_Fence->SetEventOnCompletion(m_FenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
		m_CmdAllocator->Reset();//キューをクリア
		m_CmdList->Reset(m_CmdAllocator.Get(), nullptr);//再びコマンドリストをためる準備

		m_Swapchain->Present(1, 0);


		MSG msg = {};
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//もうアプリケーションが終わるって時にmessageがWM_QUITになる
		if (msg.message == WM_QUIT) {
			return -1;
		}


		//DirectX処理
		//バックバッファのインデックスを取得
		bbIdx = m_Swapchain->GetCurrentBackBufferIndex();

		m_CmdList->ResourceBarrier(1,
			&CD3DX12_RESOURCE_BARRIER::Transition(m_BackBuffers[bbIdx],
				D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));


		//レンダーターゲットを指定
		auto rtvH = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += (SIZE_T)bbIdx*m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * bbIdx;

		//深度を指定
		/*auto dsvH = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
		m_CmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
		m_CmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);*/


		//画面クリア
		float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };//白色
		m_CmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

		//ビューポート、シザー矩形のセット
		m_CmdList->RSSetViewports(1, m_Viewport.get());
		m_CmdList->RSSetScissorRects(1, m_Scissorrect.get());


		return 0;
	}

	// ここからprivate関数

	HRESULT DX12Wrapper::CreateMainWindow()
	{
		// ウィンドウクラス生成＆登録
		WNDCLASSEX w = {};
		w.cbSize = sizeof(WNDCLASSEX);
		w.lpfnWndProc = (WNDPROC)WindowProcedure;
		w.lpszClassName = TEXT("DX12Sample");
		w.hInstance = GetModuleHandle(nullptr);

		RegisterClassEx(&w);


		// ウィンドウサイズ
		windowWidth = 1280;
		windowHeight = 720;
		RECT wrc = { 0,0,windowWidth,windowHeight };

		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


		// ウィンドウオブジェクトの生成
		m_Hwnd = CreateWindow(
			w.lpszClassName,		// クラス名
			TEXT("DX12テスト"),		// ウィンドウタイトル
			WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
			CW_USEDEFAULT,			// X
			CW_USEDEFAULT,			// Y
			wrc.right - wrc.left,	// W
			wrc.bottom - wrc.top,	// H
			nullptr,				// 親ウィンドウ
			nullptr,				// メニューハンドル
			w.hInstance,				// 追加パラメータ
			nullptr);
		return S_OK;
	}


	HRESULT DX12Wrapper::InitializeDXGIDevice()
	{
		UINT flagsDXGI = 0;
		flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
		auto result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(m_DxgiFactory.ReleaseAndGetAddressOf()));
		if (FAILED(result)) {
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

			SIZE_T videoCardMemory = (SIZE_T)(adesc.DedicatedVideoMemory / 1024 / 1024);	//(MB)

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
		for (auto level : levels) {
			if (SUCCEEDED(D3D12CreateDevice(selectedAdapter, level, IID_PPV_ARGS(m_Dev.ReleaseAndGetAddressOf())))) {
				featureLevel = level;
				result = S_OK;
				break;
			}
		}
		return result;
	}


	HRESULT DX12Wrapper::InitializeCommand() {
		auto result = m_Dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_CmdAllocator.ReleaseAndGetAddressOf()));
		if (FAILED(result)) {
			return result;
		}
		result = m_Dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CmdAllocator.Get(), nullptr, IID_PPV_ARGS(m_CmdList.ReleaseAndGetAddressOf()));
		if (FAILED(result)) {
			return result;
		}

		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;				// コマンドリストと合わせる
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				// タイムアウトなし
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// コマンドキューの優先度
		cmdQueueDesc.NodeMask = 0;										// GPUが1つの時は0、複数の時は識別用のbitを指定

		result = m_Dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_CmdQueue.ReleaseAndGetAddressOf()));//コマンドキュー生成

		return result;
	}

	HRESULT DX12Wrapper::CreateSwapChain(const HWND& hwnd) {
		RECT rc = {};
		GetWindowRect(hwnd, &rc);


		DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
		swapchainDesc.Width = rc.right - rc.left;							// 画面解像度【横】
		swapchainDesc.Height = rc.bottom - rc.top;						// 画面解像度【縦】
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				// ピクセルフォーマット
		swapchainDesc.Stereo = false;									// 3Dディスプレイかどうか
		swapchainDesc.SampleDesc.Count = 1;								// マルチサンプル指定
		swapchainDesc.SampleDesc.Quality = 0;							// マルチサンプル指定
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				// CPUのバックバッファへのアクセス方法
		swapchainDesc.BufferCount = 2;									// バッファの数。ダブルバッファのため2。
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;					// リサイズ時の挙動。見た目に合わせる。
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		// スワップ後に速やかに破棄
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// バックバッファの透過の挙動
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// ウィンドウ⇔フルスクリーン切り替え可能

		auto result = m_DxgiFactory->CreateSwapChainForHwnd(
			m_CmdQueue.Get(),
			hwnd,
			&swapchainDesc,
			nullptr,// フルスクリーン時の設定
			nullptr,// アウトプット
			(IDXGISwapChain1**)m_Swapchain.ReleaseAndGetAddressOf());
		return result;
	}


	HRESULT DX12Wrapper::CreateFinalRenderTargets() {
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		auto result = m_Swapchain->GetDesc1(&desc);

		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// レンダーターゲットビュー
		heapDesc.NodeMask = 0;								// GPUが1つの時は0、複数の時は識別用のbitを指定
		heapDesc.NumDescriptors = 2;						// ディスクリプタの数。表と裏バッファの２つ。
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// ビューの情報をシェーダから参照する必要があるか

		result = m_Dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_RtvHeaps.ReleaseAndGetAddressOf()));
		if (FAILED(result)) {
			return result;
		}


		//SRGBレンダーターゲットビュー設定(ガンマ補正)
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

		// 定義した分だけディスクリプタを生成
		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		result = m_Swapchain->GetDesc(&swcDesc);
		m_BackBuffers.resize(swcDesc.BufferCount);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();
		for (UINT i = 0; i < swcDesc.BufferCount; ++i) {
			// スワップチェーン内のメモリを取得
			auto result = m_Swapchain->GetBuffer(i, IID_PPV_ARGS(&m_BackBuffers[i]));
			// レンダ―ターゲットビューの生成(結び付け)
			m_Dev->CreateRenderTargetView(m_BackBuffers[i], &rtvDesc, handle);
			// ポインタを次のディスクリプタまで進める
			handle.ptr += m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}

		m_Viewport.reset(new CD3DX12_VIEWPORT(m_BackBuffers[0]));
		m_Scissorrect.reset(new CD3DX12_RECT(0, 0, desc.Width, desc.Height));
		return result;
	}


	HRESULT DX12Wrapper::CreateSceneView() {
		/*
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		auto result = m_Swapchain->GetDesc1(&desc);

		//定数バッファ作成
		result = m_Dev->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer((sizeof(SceneData) + 0xff) & ~0xff),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_SceneConstBuff.ReleaseAndGetAddressOf())
		);

		if (FAILED(result)) {
			return result;
		}

		_mappedSceneData = nullptr;//マップ先を示すポインタ
		result = _sceneConstBuff->Map(0, nullptr, (void**)&_mappedSceneData);//マップ

		XMFLOAT3 eye(0, 15, -15);
		XMFLOAT3 target(0, 15, 0);
		XMFLOAT3 up(0, 1, 0);
		_mappedSceneData->view = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
		_mappedSceneData->proj = XMMatrixPerspectiveFovLH(XM_PIDIV4,//画角は45°
			static_cast<float>(desc.Width) / static_cast<float>(desc.Height),//アス比
			0.1f,//近い方
			1000.0f//遠い方
		);
		_mappedSceneData->eye = eye;

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
		descHeapDesc.NodeMask = 0;//マスクは0
		descHeapDesc.NumDescriptors = 1;//
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//デスクリプタヒープ種別
		result = m_Dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(_sceneDescHeap.ReleaseAndGetAddressOf()));//生成

		////デスクリプタの先頭ハンドルを取得しておく
		auto heapHandle = _sceneDescHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = _sceneConstBuff->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = _sceneConstBuff->GetDesc().Width;
		//定数バッファビューの作成
		m_Dev->CreateConstantBufferView(&cbvDesc, heapHandle);
		return result;*/
		return S_OK;
	}

	HRESULT DX12Wrapper::CreateFence() {
		m_FenceVal = 0;
		return m_Dev->CreateFence(m_FenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_Fence.ReleaseAndGetAddressOf()));
	}
}