﻿#include "pch.h"

#include "DX12Wrapper.h"

#include "ImageTexture.h"
#include "RenderTexture.h"
#include "Shader.h"
#include "GraphicPipeline.h"
#include "Material.h"
#include "Shape.h"



#define OUT_OF_RANGE(container,index) (index<0||container.size()<=index)

namespace og
{
	SPtr<ITexture> DX12Wrapper::LoadTexture(const Path& path, const bool async)
	{
		auto texture = MSPtr<ImageTexture>(path);

		if (!texture->IsValid())return nullptr;

		return texture;
	}

	SPtr<IRenderTexture> DX12Wrapper::CreateRenderTexture(const S32 width, const S32 height, const TextureFormat format)
	{
		static ArrayList<TextureFormat> formats(1);
		formats[0] = format;
		return CreateRenderTexture(width, height, formats);
	}

	SPtr<IRenderTexture> DX12Wrapper::CreateRenderTexture(const S32 width, const S32 height, const ArrayList<TextureFormat>& formats)
	{
		ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
		ArrayList<TextureFormat> a = { TextureFormat::R16 };
		auto texture = MSPtr<RenderTexture>(formats, width, height);
		if (texture->IsValid() == false)return nullptr;
		return texture;
	}



	SPtr<IShader> DX12Wrapper::LoadShader(const String& path, ShaderType type, String& errorDest)
	{
		auto shader = Shader::LoadFromFile(path, type, errorDest);

		if (shader->IsValid() == false)return nullptr;

		return shader;
	}

	SPtr<IShader>  DX12Wrapper::CreateShader(const String& src, ShaderType type, String& errorDest)
	{
		auto shader = MSPtr<Shader>(src, type, errorDest);
		if (shader->IsValid() == false)return nullptr;
		return shader;
	}

	SPtr<IGraphicPipeline> DX12Wrapper::CreateGraphicPipeline(const GraphicPipelineDesc& desc)
	{
		auto gpipeline = MSPtr<GraphicPipeline>(desc);
		if (gpipeline->IsValid() == false)return nullptr;

		return gpipeline;
	}


	SPtr<IMaterial> DX12Wrapper::CreateMaterial(const SPtr<IGraphicPipeline>& pipeline, const S32 cBufferMask, const S32 texMask)
	{
		if (CheckArgs(!!pipeline))return nullptr;

		// シェーダーパラメータの作成
		auto material = MUPtr<Material>(pipeline, cBufferMask, texMask);
		if (material->IsValid() == false)return nullptr;

		return material;
	}

	SPtr<IShape> DX12Wrapper::CreateShape(const U32 stribeSize)
	{
		if (stribeSize <= 0)return nullptr;
		auto shape = MSPtr<Shape>(stribeSize);
		return shape;
	}
}