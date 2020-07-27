#pragma once

#include "IMaterial.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	class IGraphicPipeline;
	class ITexture;

	class Material :public IMaterial
	{
	private:
		// 依存関係
		SPtr<IGraphicPipeline> m_GraphicPipeline;
		ArrayList<SPtr<ITexture>> m_ITextureList;
		ArrayList<SPtr<ITexture>> m_ITextureListBuffer;

		// メインリソース
		ComPtr<ID3D12Resource> m_Resource;
		ComPtr<ID3D12DescriptorHeap> m_DescHeap;


		ArrayList<S32> m_resisterIndices;


		// 定数バッファマップ領域
		S32 m_DataSize;
		Byte* m_Data;
		ArrayList<S32> m_StartOffsets;
		ArrayList<S32> m_TextureNums;

		bool m_IsChanged;
		bool m_IsLocked;

		const S32 m_cBufferMask;
		const S32 m_texMask;

	public:
		Material(const SPtr<IGraphicPipeline>& gpipeline, const S32 cBufferMask = -1,const S32 texMask=-1);

		S32 SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList);

		S32 Lock()override;


		S32 SetTexture(const String& name, const SPtr<ITexture>& texture)override;

		S32 SetFloat4Param(const String& name, const Vector4& value)override;
		S32 SetMatrixParam(const String& name, const Matrix& value)override;


		inline bool IsValid()const { return m_GraphicPipeline != nullptr; };
	private:
		S32 CreateResource();
		S32 CreateDescriptorHeap();
	};
}