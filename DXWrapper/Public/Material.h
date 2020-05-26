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

	class Material
	{
	private:
		// 依存関係
		SPtr<GraphicPipeline> m_GraphicPipeline;
		ArrayList<SPtr<Texture>> m_TextureList;
		ArrayList<SPtr<Texture>> m_TextureListBuffer;

		// メインリソース
		ComPtr<ID3D12Resource> m_Resource;
		ComPtr<ID3D12DescriptorHeap> m_DescHeap;


		// 定数バッファマップ領域
		S32 m_DataSize;
		Byte* m_Data;
		ArrayList<S32> m_StartOffsets;

		bool m_IsChanged;
		bool m_IsLocked;
		S32 m_DescriptorNum;

	public:
		Material(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline, const S32 mask = -1);

		S32 SetMaterial(ComPtr<ID3D12Device>& device, ComPtr<ID3D12GraphicsCommandList>& commandList);

		S32 Lock();


		S32 SetTexture(const String& name, SPtr<Texture>& texture);

		S32 SetFloat4Param(const String& name, const Vector4& value);
		S32 SetMatrixParam(const String& name, const Matrix& value);


		inline bool IsValid()const { return m_GraphicPipeline != nullptr; };
	private:
		S32 CreateResource(ComPtr<ID3D12Device>& device, SPtr<GraphicPipeline>& gpipeline);
		S32 CreateDescriptorHeap(ComPtr<ID3D12Device>& device);
	};
}