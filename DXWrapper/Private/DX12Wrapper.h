#pragma once

#include "IDXWrapper.h"

#include <vector>

#include <d3d12.h>
#include<dxgi1_6.h>
//#include<d3dx12.h>
#include <wrl.h>

namespace OrigamiGraphic
{
	class DX12Wrapper :public IDXWrapper
	{
	public:
		int Init()override;

		int SwapScreen()override;
	private:
		// �E�B���h�E���
		HWND m_Hwnd;
		LONG windowWidth;
		LONG windowHeight;

		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		// DXGI�܂��
		ComPtr<IDXGIFactory4> m_DxgiFactory = nullptr;	// DXGI�C���^�[�t�F�C�X
		ComPtr<IDXGISwapChain4> m_Swapchain = nullptr;	// �X���b�v�`�F�C��

		// DirectX12�܂��
		ComPtr<ID3D12Device> m_Dev = nullptr;//�f�o�C�X
		ComPtr<ID3D12CommandAllocator> m_CmdAllocator = nullptr;//�R�}���h�A���P�[�^
		ComPtr<ID3D12GraphicsCommandList> m_CmdList = nullptr;//�R�}���h���X�g
		ComPtr<ID3D12CommandQueue> m_CmdQueue = nullptr;//�R�}���h�L���[

		// �\���Ɋւ��o�b�t�@����
		std::vector<ID3D12Resource*> m_BackBuffers;	//�o�b�N�o�b�t�@(2�ȏ�c�X���b�v�`�F�C�����m��)
		ComPtr<ID3D12DescriptorHeap> m_RtvHeaps = nullptr;//�����_�[�^�[�Q�b�g�p�f�X�N���v�^�q�[�v
		std::unique_ptr<D3D12_VIEWPORT> m_Viewport;//�r���[�|�[�g
		std::unique_ptr<D3D12_RECT> m_Scissorrect;//�V�U�[��`

		// �t�F���X
		ComPtr<ID3D12Fence> m_Fence = nullptr;
		UINT64 m_FenceVal = 0;


		HRESULT CreateMainWindow();
		HRESULT InitializeDXGIDevice();
		HRESULT InitializeCommand();
		HRESULT CreateSwapChain(const HWND& hwnd);
		HRESULT CreateFinalRenderTargets();
		HRESULT CreateSceneView();
		HRESULT CreateFence();
	};
}