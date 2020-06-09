#pragma once
#include "IDeletable.h"
#include "Vector3.h"

namespace og
{
	/// <summary>
	/// テクスチャを扱うための基底クラス
	/// </summary>
	class ITextureBase :public IDeletable
	{
	public:
		virtual Vector3 GetSize() = 0;
		virtual S32 GetDimension() = 0;
	};
}