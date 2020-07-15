#pragma once
#include "IDeletable.h"
namespace og
{
	class ITexture :public IDeletable
	{
	public:
		virtual Vector3 GetSize() = 0;
		virtual S32 GetDimension() = 0;
	};
}