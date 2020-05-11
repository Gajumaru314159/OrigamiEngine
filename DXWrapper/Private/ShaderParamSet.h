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
	class GraphicPipeline;
	class Texture;

	class ShaderParamSet
	{
	private:
		// 依存関係
		SPtr<GraphicPipeline> m_GraphicPipeline;
		S32 m_Index;
		ArrayList<SPtr<Texture>> m_TextureList;
		ArrayList<SPtr<Texture>> m_TextureListBuffer;

		// シェーダデータ
		ArrayList<Byte> m_Data;

		// メインリソース
		ComPtr<ID3D12Resource> m_ShaderParamResource;
		ComPtr<ID3D12DescriptorHeap> m_DescHeap;
	public:
		ShaderParamSet(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline, const S32 index);

		S32 ApplyTextures(ComPtr<ID3D12Device>& device);

		S32 SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList);


		S32 SetTexture(const String& name, SPtr<Texture>& texture);

		S32 SetFloat4Param(const String& name, const Vector4& value);


		inline bool IsValid()const { return m_DescHeap == nullptr; }
	};
}