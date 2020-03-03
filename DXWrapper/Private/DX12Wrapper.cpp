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
		// �E�B���h�E�̐���
		//======================================//
		
		if (FAILED(CreateMainWindow())) {
			return -1;
		}


		//======================================//
		// DirectX�̏�����
		//======================================//

		// �f�o�C�X�̏�����
		if (FAILED(InitializeDXGIDevice())) {
			return -1;
		}
		// �R�}���h�L���[�̏�����
		if (FAILED(InitializeCommand())) {
			return -1;
		}
		// �X���b�v�`�F�[���̍쐬
		if (FAILED(CreateSwapChain(m_Hwnd))) {
			return -1;
		}
		// �ŏI�����_�����O��̍쐬
		if (FAILED(CreateFinalRenderTargets())) {
			return -1;
		}
		// �����_�����O�Ɏg�p����ϊ��s��̒�`
		if (FAILED(CreateSceneView())) {
			return -1;
		}
		//�t�F���X�̍쐬
		if (FAILED(CreateFence())) {
			return -1;
		}

		// �e�N�X�`�����[�h�e�[�u���̍쐬
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

		//���߂̃N���[�Y
		m_CmdList->Close();



		//�R�}���h���X�g�̎��s
		ID3D12CommandList* cmdlists[] = { m_CmdList.Get() };
		m_CmdQueue->ExecuteCommandLists(1, cmdlists);
		////�҂�
		m_CmdQueue->Signal(m_Fence.Get(), ++m_FenceVal);

		if (m_Fence->GetCompletedValue() < m_FenceVal) {
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_Fence->SetEventOnCompletion(m_FenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
		m_CmdAllocator->Reset();//�L���[���N���A
		m_CmdList->Reset(m_CmdAllocator.Get(), nullptr);//�ĂуR�}���h���X�g�����߂鏀��

		m_Swapchain->Present(1, 0);


		MSG msg = {};
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//�����A�v���P�[�V�������I�����Ď���message��WM_QUIT�ɂȂ�
		if (msg.message == WM_QUIT) {
			return -1;
		}


		//DirectX����
		//�o�b�N�o�b�t�@�̃C���f�b�N�X���擾
		bbIdx = m_Swapchain->GetCurrentBackBufferIndex();

		m_CmdList->ResourceBarrier(1,
			&CD3DX12_RESOURCE_BARRIER::Transition(m_BackBuffers[bbIdx],
				D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));


		//�����_�[�^�[�Q�b�g���w��
		auto rtvH = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += (SIZE_T)bbIdx*m_Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * bbIdx;

		//�[�x���w��
		/*auto dsvH = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
		m_CmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
		m_CmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);*/


		//��ʃN���A
		float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };//���F
		m_CmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

		//�r���[�|�[�g�A�V�U�[��`�̃Z�b�g
		m_CmdList->RSSetViewports(1, m_Viewport.get());
		m_CmdList->RSSetScissorRects(1, m_Scissorrect.get());


		return 0;
	}

	// ��������private�֐�

	HRESULT DX12Wrapper::CreateMainWindow()
	{
		// �E�B���h�E�N���X�������o�^
		WNDCLASSEX w = {};
		w.cbSize = sizeof(WNDCLASSEX);
		w.lpfnWndProc = (WNDPROC)WindowProcedure;
		w.lpszClassName = TEXT("DX12Sample");
		w.hInstance = GetModuleHandle(nullptr);

		RegisterClassEx(&w);


		// �E�B���h�E�T�C�Y
		windowWidth = 1280;
		windowHeight = 720;
		RECT wrc = { 0,0,windowWidth,windowHeight };

		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


		// �E�B���h�E�I�u�W�F�N�g�̐���
		m_Hwnd = CreateWindow(
			w.lpszClassName,		// �N���X��
			TEXT("DX12�e�X�g"),		// �E�B���h�E�^�C�g��
			WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
			CW_USEDEFAULT,			// X
			CW_USEDEFAULT,			// Y
			wrc.right - wrc.left,	// W
			wrc.bottom - wrc.top,	// H
			nullptr,				// �e�E�B���h�E
			nullptr,				// ���j���[�n���h��
			w.hInstance,				// �ǉ��p�����[�^
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


		// �A�_�v�^�[�̗񋓂��A�������ʂ��ő�̃O���t�B�b�N�{�[�h��I��
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



		// �Ή����Ă��郌�x���Ő���
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
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;				// �R�}���h���X�g�ƍ��킹��
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				// �^�C���A�E�g�Ȃ�
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// �R�}���h�L���[�̗D��x
		cmdQueueDesc.NodeMask = 0;										// GPU��1�̎���0�A�����̎��͎��ʗp��bit���w��

		result = m_Dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_CmdQueue.ReleaseAndGetAddressOf()));//�R�}���h�L���[����

		return result;
	}

	HRESULT DX12Wrapper::CreateSwapChain(const HWND& hwnd) {
		RECT rc = {};
		GetWindowRect(hwnd, &rc);


		DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
		swapchainDesc.Width = rc.right - rc.left;							// ��ʉ𑜓x�y���z
		swapchainDesc.Height = rc.bottom - rc.top;						// ��ʉ𑜓x�y�c�z
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				// �s�N�Z���t�H�[�}�b�g
		swapchainDesc.Stereo = false;									// 3D�f�B�X�v���C���ǂ���
		swapchainDesc.SampleDesc.Count = 1;								// �}���`�T���v���w��
		swapchainDesc.SampleDesc.Quality = 0;							// �}���`�T���v���w��
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				// CPU�̃o�b�N�o�b�t�@�ւ̃A�N�Z�X���@
		swapchainDesc.BufferCount = 2;									// �o�b�t�@�̐��B�_�u���o�b�t�@�̂���2�B
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;					// ���T�C�Y���̋����B�����ڂɍ��킹��B
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		// �X���b�v��ɑ��₩�ɔj��
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// �o�b�N�o�b�t�@�̓��߂̋���
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// �E�B���h�E�̃t���X�N���[���؂�ւ��\

		auto result = m_DxgiFactory->CreateSwapChainForHwnd(
			m_CmdQueue.Get(),
			hwnd,
			&swapchainDesc,
			nullptr,// �t���X�N���[�����̐ݒ�
			nullptr,// �A�E�g�v�b�g
			(IDXGISwapChain1**)m_Swapchain.ReleaseAndGetAddressOf());
		return result;
	}


	HRESULT DX12Wrapper::CreateFinalRenderTargets() {
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		auto result = m_Swapchain->GetDesc1(&desc);

		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// �����_�[�^�[�Q�b�g�r���[
		heapDesc.NodeMask = 0;								// GPU��1�̎���0�A�����̎��͎��ʗp��bit���w��
		heapDesc.NumDescriptors = 2;						// �f�B�X�N���v�^�̐��B�\�Ɨ��o�b�t�@�̂Q�B
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// �r���[�̏����V�F�[�_����Q�Ƃ���K�v�����邩

		result = m_Dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_RtvHeaps.ReleaseAndGetAddressOf()));
		if (FAILED(result)) {
			return result;
		}


		//SRGB�����_�[�^�[�Q�b�g�r���[�ݒ�(�K���}�␳)
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

		// ��`�����������f�B�X�N���v�^�𐶐�
		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		result = m_Swapchain->GetDesc(&swcDesc);
		m_BackBuffers.resize(swcDesc.BufferCount);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_RtvHeaps->GetCPUDescriptorHandleForHeapStart();
		for (UINT i = 0; i < swcDesc.BufferCount; ++i) {
			// �X���b�v�`�F�[�����̃��������擾
			auto result = m_Swapchain->GetBuffer(i, IID_PPV_ARGS(&m_BackBuffers[i]));
			// �����_�\�^�[�Q�b�g�r���[�̐���(���ѕt��)
			m_Dev->CreateRenderTargetView(m_BackBuffers[i], &rtvDesc, handle);
			// �|�C���^�����̃f�B�X�N���v�^�܂Ői�߂�
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

		//�萔�o�b�t�@�쐬
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

		_mappedSceneData = nullptr;//�}�b�v��������|�C���^
		result = _sceneConstBuff->Map(0, nullptr, (void**)&_mappedSceneData);//�}�b�v

		XMFLOAT3 eye(0, 15, -15);
		XMFLOAT3 target(0, 15, 0);
		XMFLOAT3 up(0, 1, 0);
		_mappedSceneData->view = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
		_mappedSceneData->proj = XMMatrixPerspectiveFovLH(XM_PIDIV4,//��p��45��
			static_cast<float>(desc.Width) / static_cast<float>(desc.Height),//�A�X��
			0.1f,//�߂���
			1000.0f//������
		);
		_mappedSceneData->eye = eye;

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
		descHeapDesc.NodeMask = 0;//�}�X�N��0
		descHeapDesc.NumDescriptors = 1;//
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//�f�X�N���v�^�q�[�v���
		result = m_Dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(_sceneDescHeap.ReleaseAndGetAddressOf()));//����

		////�f�X�N���v�^�̐擪�n���h�����擾���Ă���
		auto heapHandle = _sceneDescHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = _sceneConstBuff->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = _sceneConstBuff->GetDesc().Width;
		//�萔�o�b�t�@�r���[�̍쐬
		m_Dev->CreateConstantBufferView(&cbvDesc, heapHandle);
		return result;*/
		return S_OK;
	}

	HRESULT DX12Wrapper::CreateFence() {
		m_FenceVal = 0;
		return m_Dev->CreateFence(m_FenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_Fence.ReleaseAndGetAddressOf()));
	}
}