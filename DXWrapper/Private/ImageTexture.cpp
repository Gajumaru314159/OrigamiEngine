#include "pch.h"
#include "ImageTexture.h"
#include <d3dx12.h>
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

#include "DX12Wrapper.h"


namespace og
{
	ImageTexture::ImageTexture(const Path& path) :m_path(path)
	{
		if (CheckArgs(path.IsValid()))return;

		// 非対応の拡張子なら失敗
		auto extention = m_path.Extension();
		if (s_ImageFormatMap.count(extention) == 0)return;

		// テクスチャ読み込み関数用にワイド文字に変換
		WCHAR wStrW[1024];
		size_t wLen = 0;
		mbstowcs_s(&wLen, wStrW, 1024, path.ToString().c_str(), _TRUNCATE);

		// 拡張子に合わせて読み込み
		HRESULT result;
		DirectX::TexMetadata metadata = {};
		DirectX::ScratchImage scratchImg = {};
		switch (s_ImageFormatMap[extention])
		{
		case ImageFileFormat::DDS:result = DirectX::LoadFromDDSFile(wStrW, DirectX::DDS_FLAGS_NONE, &metadata, scratchImg); break;
		case ImageFileFormat::HDR:result = DirectX::LoadFromHDRFile(wStrW, &metadata, scratchImg); break;
		case ImageFileFormat::TGA:result = DirectX::LoadFromTGAFile(wStrW, &metadata, scratchImg); break;
		case ImageFileFormat::WIC:result = DirectX::LoadFromWICFile(wStrW, DirectX::WIC_FLAGS_NONE, &metadata, scratchImg); break;
		}
		if (FAILED(result))return;


		//WriteToSubresourceで転送する用のヒープ設定
		auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		auto resDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			metadata.format,
			(UINT16)metadata.width,
			(UINT)metadata.height,
			(UINT16)metadata.arraySize,
			(UINT16)metadata.mipLevels);


		ComPtr<ID3D12Resource> resource;

		result = DX12Wrapper::ms_device->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));

		if (FAILED(result))return;


		// GPUにデータ転送
		auto img = scratchImg.GetImage(0, 0, 0);

		result = resource->WriteToSubresource(0,
			nullptr,               //全領域へコピー
			img->pixels,           //元データアドレス
			(UINT)img->rowPitch,   //1ラインサイズ
			(UINT)img->slicePitch  //全サイズ
		);
		if (FAILED(result))return;

		m_resources.push_back(resource);
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


	void ImageTexture::Reload()
	{
		// 画像の再読み込み処理
	}

	S32 ImageTexture::GetImageFormatSize(const DXGI_FORMAT format)
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

	HashMap<String, ImageFileFormat> ImageTexture::s_ImageFormatMap =
	{
		{TC("dds")	,ImageFileFormat::DDS},
		{TC("tga")	,ImageFileFormat::TGA},
		{TC("tga")	,ImageFileFormat::HDR},
		{TC("bmp")	,ImageFileFormat::WIC},
		{TC("png")	,ImageFileFormat::WIC},
		{TC("jpg")	,ImageFileFormat::WIC},
		{TC("jpeg")	,ImageFileFormat::WIC},
		{TC("png")	,ImageFileFormat::WIC},
		{TC("tiff")	,ImageFileFormat::WIC}
	};

}