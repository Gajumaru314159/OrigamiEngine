#pragma once

#include "ITexture.h"

#include <d3d12.h>
#include <wrl.h>

namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace og
{
	enum class TextureFileFormat
	{
		DDS,
		HDR,
		TGA,
		WIC
	};

	class Texture :public ITexture
	{
	private:
		ComPtr<ID3D12Resource> m_Resource;

		Path m_Path;
	public:
		Texture(ComPtr<ID3D12Device>& device, const Path& path);
		//Texture(ComPtr<ID3D12Device>& device, const U32 width, const U32 height, const DXGI_FORMAT format);

		S32 CreateShaderResourceView(ComPtr<ID3D12Device>& device, D3D12_CPU_DESCRIPTOR_HANDLE& handle);


		inline bool IsValid()const { return m_Resource != nullptr; }


		Vector3 GetSize()override;
		S32 GetDimension() override;

		bool IsLoaded() override;

	public:
		static S32 GetTextureFormatSize(const DXGI_FORMAT format);
	private:
		static HashMap<String, TextureFileFormat> s_TextureFormatMap;
	};
}