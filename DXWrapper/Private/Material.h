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
		SPtr<IGraphicPipeline> m_graphicPipeline;
		ArrayList<SPtr<ITexture>> m_textureList;
		ArrayList<SPtr<ITexture>> m_textureListBuffer;

		// メインリソース
		ComPtr<ID3D12Resource> m_resource;
		ComPtr<ID3D12DescriptorHeap> m_descHeap;


		ArrayList<S32> m_resisterIndices;


		// 定数バッファマップ領域
		S32 m_dataSize;
		Byte* m_data;
		ArrayList<S32> m_startOffsets;
		ArrayList<S32> m_textureNums;

		bool m_isChanged;
		bool m_isLocked;

		const S32 m_cBufferMask;
		const S32 m_texMask;


		ArrayList<S32> m_targets;

	public:
		Material(const SPtr<IGraphicPipeline>& gpipeline, const S32 cBufferMask = -1, const S32 texMask = -1);

		S32 SetMaterial(ComPtr<ID3D12GraphicsCommandList>& commandList);

		S32 Lock()override;


		S32 SetTexture(const String& name, const SPtr<ITexture>& texture, const S32 target)override;

		S32 SetFloat4Param(const String& name, const Vector4& value)override;
		S32 SetMatrixParam(const String& name, const Matrix& value)override;


		inline bool IsValid()const { return m_graphicPipeline != nullptr; };
	private:
		S32 CreateResource();
		S32 CreateDescriptorHeap();
	};
}