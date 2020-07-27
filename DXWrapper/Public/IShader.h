#pragma once
#include "IDeletable.h"

namespace og
{
	/// <summary>
	/// シェーダの種類
	/// </summary>
	enum class ShaderType
	{
		VERTEX,
		PIXEL
	};


	class IShader :public IDeletable
	{
	};
}