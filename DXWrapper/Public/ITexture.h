#pragma once
#include "IDeletable.h"
namespace og
{
	/// <summary>
	/// テクスチャフォーマット
	/// </summary>
	enum class TextureFormat
	{
		// RGBA
		RGBA32,
		RGBA16,
		RGBA8,
		// RG(Normal)
		RG8,
		// R
		R32,
		R16,
		R8,
		// D24S8
		Depth,
		// Other
		RGB565,
		RGBA5551
	};

	class ITexture :public IDeletable
	{
	public:
		virtual Vector3 GetSize() = 0;
		virtual S32 GetDimension() = 0;
	};
}