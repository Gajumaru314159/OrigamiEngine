#pragma once
#include "ITextureBase.h"
namespace og
{
	class IShape;

	class IRenderTexture :public ITextureBase
	{
	public:
		virtual S32 DrawInstanced(SPtr<IShape>& shape, const U32 count = 1) = 0;


	};
}