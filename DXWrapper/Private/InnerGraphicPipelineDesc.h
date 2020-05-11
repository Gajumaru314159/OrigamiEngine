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
	struct InnerGraphicPipelineDesc :public GraphicPipelineDesc
	{
		InnerGraphicPipelineDesc(const GraphicPipelineDesc& desc) :GraphicPipelineDesc(desc) {}

		ComPtr<ID3DBlob> vsBolb;
		ComPtr<ID3DBlob> psBolb;
		ComPtr<ID3DBlob> gsBolb;
		ComPtr<ID3DBlob> hsBolb;
		ComPtr<ID3DBlob> dsBolb;
	};
}