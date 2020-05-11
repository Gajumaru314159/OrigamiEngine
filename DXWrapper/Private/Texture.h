#pragma once

#include <d3d12.h>
#include <wrl.h>

namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace og
{
	class Texture
	{
	private:
		ComPtr<ID3D12Resource> m_Resource;
	public:
		Texture(ComPtr<ID3D12Device>& device, const String& path);
		Texture(ComPtr<ID3D12Device>& device, const U32 width, const U32 height, const DXGI_FORMAT format);


		S32 CreateShaderResourceView(ComPtr<ID3D12Device>& device, D3D12_CPU_DESCRIPTOR_HANDLE& handle);

		inline bool IsValid()const { return m_Resource != nullptr; }

	public:
		static S32 GetTextureFormatSize(const DXGI_FORMAT format);
	private:
		enum class TextureFormat
		{
			DDS,
			HDR,
			TGA,
			WIC
		};
		static HashMap<String, TextureFormat> s_TextureFormatMap;
	};
}