#include "pch.h"
#include "RenderTexture.h"
#include "GraphicPipeline.h"
#include "Material.h"
#include "Shape.h"

#include <d3dx12.h>
#include "DX12Wrapper.h"
namespace og
{
	RenderTexture::RenderTexture(const DXGI_FORMAT format, const U32 width, const U32 height,const bool useDepth)
	{
		m_clearColor.Set(0.0f,0.0f,0.0f);

		HRESULT result;
		ComPtr<ID3D12Resource> resource;

		// メインリソースの生成
		{
			// リソースの生成
			{
				auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
				auto resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height);

				resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

				float clearColor[4] = { 0.0,0.0,0.0,1.0 };
				auto clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor);


				result = DX12Wrapper::ms_device->CreateCommittedResource(
					&texHeapProp,
					D3D12_HEAP_FLAG_NONE,
					&resourceDesc,
					D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
					&clearValue,
					IID_PPV_ARGS(resource.ReleaseAndGetAddressOf())
				);
				if (FAILED(result))
				{
					return;
				}
			}


			// RTVディスクリプタの生成
			{
				D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
				heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				heapDesc.NodeMask = 0;
				heapDesc.NumDescriptors = 1;
				heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

				result = DX12Wrapper::ms_device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_rtvHeap.ReleaseAndGetAddressOf()));
				if (FAILED(result))
				{
					return;
				}

				// レンダーターゲットビューの生成
				D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
				rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
				rtvDesc.Format = format;

				DX12Wrapper::ms_device->CreateRenderTargetView(resource.Get(), &rtvDesc, m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
			}


			// SRVディスクリプタの生成
			{
				D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
				heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				heapDesc.NodeMask = 0;
				heapDesc.NumDescriptors = 1;
				heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;


				result = DX12Wrapper::ms_device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_srvHeap.ReleaseAndGetAddressOf()));
				if (FAILED(result))
				{
					return;
				}

				D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Format = format;
				srvDesc.Texture2D.MipLevels = 1;
				srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

				DX12Wrapper::ms_device->CreateShaderResourceView(m_resource.Get(), &srvDesc, m_srvHeap->GetCPUDescriptorHandleForHeapStart());
			}

		}

		// デプスリソースの生成
		{
			auto depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, width, height);
			depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			auto depthHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

			D3D12_CLEAR_VALUE _depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
			result = DX12Wrapper::ms_device->CreateCommittedResource(
				&depthHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&depthResDesc,
				D3D12_RESOURCE_STATE_DEPTH_WRITE,
				&_depthClearValue,
				IID_PPV_ARGS(m_depth.ReleaseAndGetAddressOf()));




			//深度のためのデスクリプタヒープ作成
			D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
			dsvHeapDesc.NumDescriptors = 1;
			dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

			result = DX12Wrapper::ms_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_dsvHeap.ReleaseAndGetAddressOf()));


			//深度ビュー作成
			D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
			dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//デプス値に32bit使用
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
			DX12Wrapper::ms_device->CreateDepthStencilView(m_depth.Get(), &dsvDesc, m_dsvHeap->GetCPUDescriptorHandleForHeapStart());

		}


		result = DX12Wrapper::ms_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdAllocator.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return;
		}
		result = DX12Wrapper::ms_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(), nullptr, IID_PPV_ARGS(m_cmdList.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return;
		}


		m_resource = resource;

		m_viewport = CD3DX12_VIEWPORT(m_resource.Get());
		m_scissorrect = CD3DX12_RECT(0, 0, (U32)m_viewport.Width, (U32)m_viewport.Height);

	}





	ID3D12GraphicsCommandList* RenderTexture::GetCommandList()
	{
		return m_cmdList.Get();
	}

	void RenderTexture::ResetCommand()
	{
		m_cmdAllocator->Reset();
		m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
	}



	S32 RenderTexture::BeginDraw()
	{
		// 描画のための初期コマンドを記録
		auto rtvHeapPointr = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
		m_cmdList->OMSetRenderTargets(1, &rtvHeapPointr, false, &m_dsvHeap->GetCPUDescriptorHandleForHeapStart());

		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_resource
			.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET));




		auto rtvH = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();

		float clearColor[] = { m_clearColor.r,m_clearColor.g,m_clearColor.b,m_clearColor.a };
		m_cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
		
		// TODO デプスのクリア
		//m_cmdList->ClearDepthStencilView();

		//ビューポート、シザー矩形のセット
		m_cmdList->RSSetViewports(1, &m_viewport);
		m_cmdList->RSSetScissorRects(1, &m_scissorrect);
		return 0;
	}

	S32 RenderTexture::EndDraw()
	{
		m_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_resource
			.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
		m_cmdList->Close();
		DX12Wrapper::ms_renderTextureQueue.push_back(this);
		return 0;
	}


	S32 RenderTexture::SetGraphicPipeline(SPtr<IGraphicPipeline> pipeline)
	{
		if (CheckArgs(!!pipeline))return -1;
		auto ptr = reinterpret_cast<GraphicPipeline*>(pipeline.get());
		ptr->SetGraphicPipeline(m_cmdList);

		return 0;
	}

	S32 RenderTexture::SetMaterial(SPtr<IMaterial> material)
	{
		if (CheckArgs(!!material))return -1;
		auto ptr = reinterpret_cast<Material*>(material.get());
		ptr->SetMaterial(m_cmdList);
		return 0;
	}


	S32 RenderTexture::DrawInstanced(SPtr<IShape>& shape, const U32 count)
	{
		if (CheckArgs(!!shape))return -1;

		auto ptr = reinterpret_cast<Shape*>(shape.get());
		ptr->Draw(m_cmdList, count);
		return 0;
	}




	Vector3 RenderTexture::GetSize()
	{
		// TODO Vector3Intを作る
		if (IsValid() == false)return Vector3();
		auto desc = m_resource->GetDesc();
		return Vector3((F32)desc.Width, (F32)desc.Height, (F32)desc.DepthOrArraySize);
	}

	S32 RenderTexture::GetDimension()
	{
		if (IsValid() == false)return 0;
		auto desc = m_resource->GetDesc();
		return desc.Dimension;
	}

	void RenderTexture::SetClearColor(Color color)
	{
		m_clearColor = color;
	}
}