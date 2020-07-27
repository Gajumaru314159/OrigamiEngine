#pragma once
#include "ITexture.h"

namespace og
{
	class IGraphicPipeline;
	class IMaterial;
	class IShape;


	class IRenderTexture :public ITexture
	{
	public:
		virtual S32 BeginDraw() = 0;
		virtual S32 EndDraw() = 0;

		virtual S32 SetGraphicPipeline(SPtr<IGraphicPipeline> pipeline) = 0;

		virtual S32 SetMaterial(SPtr<IMaterial> material) = 0;

		virtual S32 DrawInstanced(SPtr<IShape>& shape, const U32 count = 1) = 0;


		virtual void SetClearColor(Color color)=0;
	};
}