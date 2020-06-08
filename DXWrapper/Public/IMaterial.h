﻿#pragma once

#include "IDeletable.h"

namespace og
{
	class Texture;

	class IMaterial :public IDeletable
	{
	public:
		virtual void Delete() { delete this; };

		virtual S32 Lock() = 0;

		virtual S32 SetTexture(const String& name, SPtr<Texture>& texture) = 0;

		virtual S32 SetFloat4Param(const String& name, const Vector4& value) = 0;
		virtual S32 SetMatrixParam(const String& name, const Matrix& value) = 0;
	};
}