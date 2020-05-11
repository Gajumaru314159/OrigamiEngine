#pragma once

#include <d3d12.h>
#include <wrl.h>
#include <Texture.h>

namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}

namespace og
{
	class DefaultAsset :public Singleton<DefaultAsset>
	{
		friend class Singleton<DefaultAsset>;
	public:
		SPtr<Texture> whiteTex;
	};
}