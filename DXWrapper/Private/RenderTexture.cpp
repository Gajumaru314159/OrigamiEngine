#include "pch.h"
#include "RenderTexture.h"
#include "Shape.h"
#include <d3dx12.h>

namespace og
{
	RenderTexture::RenderTexture(ComPtr<ID3D12Device>& device, const DXGI_FORMAT format, const U32 width, const U32 height)
	{
		if (CheckArgs(device))return;
		if (width == 0 || height == 0)return;

		// リソースの生成
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height);
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		float col[4] = { 0,0,0,1 };
		auto clearValue = CD3DX12_CLEAR_VALUE(format, col);

		ComPtr<ID3D12Resource> resource;

		auto result = device->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&clearValue,
			IID_PPV_ARGS(resource.ReleaseAndGetAddressOf())
		);
		if (FAILED(result))
		{
			return;
		}


		// ディスクリプタヒープの生成

		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 1;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		result = device->CreateDescriptorHeap(
			&heapDesc,
			IID_PPV_ARGS(m_RTVHeap.ReleaseAndGetAddressOf())
		);
		if (FAILED(result))
		{
			return;
		}

		// レンダーターゲットビューの生成
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Format = format;

		device->CreateRenderTargetView(
			resource.Get(),
			&rtvDesc,
			m_RTVHeap->GetCPUDescriptorHandleForHeapStart()
		);

		//SRV用ヒープ
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		result = device->CreateDescriptorHeap(
			&heapDesc,
			IID_PPV_ARGS(m_SRVHeap.ReleaseAndGetAddressOf())
		);
		if (FAILED(result))
		{
			return;
		}

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format = rtvDesc.Format;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		device->CreateShaderResourceView(
			m_Resource.Get(),
			&srvDesc,
			m_SRVHeap->GetCPUDescriptorHandleForHeapStart()
		);


		m_Resource = resource;
	}


	S32 RenderTexture::DrawInstanced(SPtr<IShape>& shape, const U32 count)
	{
		if (CheckArgs(!!shape))return -1;

		auto ptr = reinterpret_cast<Shape*>(shape.get());
		ptr->Draw(m_ComList, count);
		return 0;
	}


	Vector3 RenderTexture::GetSize()
	{
		auto desc = m_Resource->GetDesc();
		return Vector3(desc.Width, desc.Height, desc.DepthOrArraySize);
	}

	S32 RenderTexture::GetDimension()
	{
		auto desc = m_Resource->GetDesc();
		return desc.Dimension;
	}
}