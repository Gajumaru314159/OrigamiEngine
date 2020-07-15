#pragma once

#include "Texture.h"
#include "IImageTexture.h"

#include <d3d12.h>
#include "DXHelper.h"

namespace og
{
	enum class ImageFileFormat
	{
		DDS,
		HDR,
		TGA,
		WIC
	};

	class IGraphicPipeline;

	class ImageTexture :public Texture, public IImageTexture
	{
	private:
		Path m_Path;
	public:
		ImageTexture(const Path& path);

		void Reload()override;
	public:
		static S32 GetImageFormatSize(const DXGI_FORMAT format);
	private:
		static HashMap<String, ImageFileFormat> s_ImageFormatMap;
	};
}