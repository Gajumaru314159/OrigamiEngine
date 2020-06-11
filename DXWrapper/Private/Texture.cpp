#include "pch.h"
#include "Texture.h"
#include <d3dx12.h>
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")


namespace og
{
	Texture::Texture(ComPtr<ID3D12Device>& device, const Path& path) :m_Path(path)
	{
		if (CheckArgs(device, path.IsValid()))return;

		//テクスチャのロード
		DirectX::TexMetadata metadata = {};
		DirectX::ScratchImage scratchImg = {};


		auto extention = m_Path.Extension();

		// 非対応の拡張子なら失敗
		if (s_TextureFormatMap.count(extention) == 0)return;

		//変換文字列格納バッファ
		WCHAR	wStrW[1024];
		size_t wLen = 0;
		mbstowcs_s(&wLen, wStrW, 1024, path.ToString().c_str(), _TRUNCATE);


		HRESULT result;
		switch (s_TextureFormatMap[extention])
		{
		case TextureFileFormat::DDS:result = DirectX::LoadFromDDSFile(wStrW, DirectX::DDS_FLAGS_NONE, &metadata, scratchImg); break;
		case TextureFileFormat::HDR:result = DirectX::LoadFromHDRFile(wStrW, &metadata, scratchImg); break;
		case TextureFileFormat::TGA:result = DirectX::LoadFromTGAFile(wStrW, &metadata, scratchImg); break;
		case TextureFileFormat::WIC:result = DirectX::LoadFromWICFile(wStrW, DirectX::WIC_FLAGS_NONE, &metadata, scratchImg); break;
		}
		if (FAILED(result))return;

		auto img = scratchImg.GetImage(0, 0, 0);  //生データ抽出



		//WriteToSubresourceで転送する用のヒープ設定
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			metadata.format,
			(UINT16)metadata.width,
			(UINT)metadata.height,
			(UINT16)metadata.arraySize,
			(UINT16)metadata.mipLevels);


		ComPtr<ID3D12Resource> resource;

		result = device->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));

		if (FAILED(result))return;

		result = resource->WriteToSubresource(0,
											  nullptr,               //全領域へコピー
											  img->pixels,           //元データアドレス
											  (UINT)img->rowPitch,   //1ラインサイズ
											  (UINT)img->slicePitch  //全サイズ
		);
		if (FAILED(result))return;

		m_Resource = resource;
	}

	/*
	Texture::Texture(ComPtr<ID3D12Device>& device, const U32 width, const U32 height, const DXGI_FORMAT format)
	{
		if (CheckArgs(device))return;

		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height);
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);


		ComPtr<ID3D12Resource> resource;

		auto result = device->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(resource.ReleaseAndGetAddressOf())
		);
		if (FAILED(result))
		{
			return;
		}

		std::vector<Byte> data(width * height * GetTextureFormatSize(format), 0xff);
		//std::fill(data.begin(), data.end(), 0xff);

		result = resource->WriteToSubresource(0, nullptr, data.data(), width * height, (U32)data.size());
		if (FAILED(result))
		{
			return;
		}
		m_Resource = resource;
	}
	*/


	S32 Texture::CreateShaderResourceView(ComPtr<ID3D12Device>& device, D3D12_CPU_DESCRIPTOR_HANDLE& handle)
	{
		if (CheckArgs(device, !!m_Resource))return 0;

		D3D12_SHADER_RESOURCE_VIEW_DESC texDesc = {};
		texDesc.Format = m_Resource->GetDesc().Format;
		texDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		texDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		texDesc.Texture2D.MipLevels = 1;

		device->CreateShaderResourceView(
			m_Resource.Get(),
			&texDesc,
			handle
		);

		handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		return 0;
	}


	Vector3 Texture::GetSize()
	{
		// TODO Vector3Intを作る
		if (IsValid() == false)return Vector3();
		auto desc = m_Resource->GetDesc();
		return Vector3((F32)desc.Width, (F32)desc.Height, (F32)desc.DepthOrArraySize);
	}

	S32 Texture::GetDimension()
	{
		if (IsValid() == false)return 0;
		auto desc = m_Resource->GetDesc();
		return desc.Dimension;
	}


	bool Texture::IsLoaded()
	{
		// TODO 非同期のテクスチャ読み込み
		return true;
	}





	S32 Texture::GetTextureFormatSize(const DXGI_FORMAT format)
	{
		switch (format)
		{
		case DXGI_FORMAT_R32G32B32A32_FLOAT:return 16;
		case DXGI_FORMAT_R16G16B16A16_UNORM:return 8;
		case DXGI_FORMAT_R8G8B8A8_UNORM:	return 4;
		case DXGI_FORMAT_R8G8_SNORM:		return 2;
		case DXGI_FORMAT_R32_FLOAT:			return 4;
		case DXGI_FORMAT_R16_UNORM:			return 2;
		case DXGI_FORMAT_R8_UNORM:			return 1;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:	return 4;
		case DXGI_FORMAT_B5G6R5_UNORM:		return 2;
		case DXGI_FORMAT_B5G5R5A1_UNORM:	return 2;
		}
		return 0;
	}

	HashMap<String, TextureFileFormat> Texture::s_TextureFormatMap =
	{
		{TC("dds")	,TextureFileFormat::DDS},
		{TC("tga")	,TextureFileFormat::TGA},
		{TC("tga")	,TextureFileFormat::HDR},
		{TC("bmp")	,TextureFileFormat::WIC},
		{TC("png")	,TextureFileFormat::WIC},
		{TC("jpg")	,TextureFileFormat::WIC},
		{TC("jpeg")	,TextureFileFormat::WIC},
		{TC("png")	,TextureFileFormat::WIC},
		{TC("tiff")	,TextureFileFormat::WIC}
	};

}