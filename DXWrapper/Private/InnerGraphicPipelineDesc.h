#pragma once

#include "GraphicPipelineDesc.h"

#include "DXHelper.h"


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