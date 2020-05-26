#pragma once

#include<wrl.h>

#include "GraphicPipelineDesc.h"


namespace
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
}


namespace og
{
	class Shader;
	struct InnerGraphicPipelineDesc :public GraphicPipelineDesc
	{
		InnerGraphicPipelineDesc(const GraphicPipelineDesc& desc) :GraphicPipelineDesc(desc) {}

		SPtr<Shader> vsInstance;
		SPtr<Shader> psInstance;
		SPtr<Shader> gsInstance;
		SPtr<Shader> hsInstance;
		SPtr<Shader> dsInstance;
	};
}