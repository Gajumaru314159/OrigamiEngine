#pragma once
#include "ITextureBase.h"
namespace og
{
	/// <summary>
	/// 読み込み専用のテクスチャ
	/// </summary>
	/// <remarks>
	/// 動的に生成するテクスチャはIRenderTextureを使用してください
	/// </remarks>
	class ITexture : public ITextureBase
	{
	public:
		static SPtr<ITexture> whiteTexture;
		static SPtr<ITexture> blackTexture;
		static SPtr<ITexture> normalTexture;


		virtual bool IsLoaded() = 0;
	};
}