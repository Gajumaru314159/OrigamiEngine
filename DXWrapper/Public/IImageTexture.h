#pragma once
#include "IDeletable.h"

namespace og
{
	/// <summary>
	/// 読み込み専用のテクスチャ
	/// </summary>
	/// <remarks>
	/// 動的に生成するテクスチャはIRenderTextureを使用してください
	/// </remarks>
	class IImageTexture : public IDeletable

	{
	public:
		virtual void Reload() = 0;
	};
}