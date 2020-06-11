#pragma once
#include "ITextureBase.h"
namespace og
{
	class IRenderTexture :public ITextureBase
	{
	public:
		virtual S32 Draw() = 0;
	};
}