#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <Texture.h>

#include "DXHelper.h"

namespace og
{
	class DefaultAsset :public Singleton<DefaultAsset>
	{
		friend class Singleton<DefaultAsset>;
	public:
		SPtr<Texture> whiteTex;
	};
}