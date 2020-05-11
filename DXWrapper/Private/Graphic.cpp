﻿#include "pch.h"

#include "DX12Wrapper.h"

#include "Texture.h"
#include "Shader.h"
#include "GraphicPipeline.h"
#include "Material.h"
#include "Shape.h"



#define OUT_OF_RANGE(container,index) (index<0||container.size()<=index)

namespace og
{
	S32 DX12Wrapper::LoadGraph(const String& path)
	{
		auto texture = MSPtr<Texture>(m_Dev, path);

		if (!texture->IsValid())return -1;

		m_TextureList.push_back(texture);

		return (int)m_TextureList.size() - 1;
	}

	S32 DX12Wrapper::CreateTexture(const S32 width, const S32 height, const TextureFormat format)
	{
		auto texture = MSPtr<Texture>(m_Dev, width, height, ConvertTextureFormat(format));

		if (!texture->IsValid())return -1;

		m_TextureList.push_back(texture);
		return (S32)m_TextureList.size() - 1;
	}



	S32 DX12Wrapper::LoadShader(const String& path, ShaderType type, String& errorDest)
	{
		auto shader = Shader::LoadFromFile(path, type, errorDest);

		if (!shader->IsValid())return -1;

		m_ShaderList.push_back(std::move(shader));
		return (S32)m_ShaderList.size() - 1;
	}

	S32 DX12Wrapper::CreateShader(const String& src, ShaderType type, String& errorDest)
	{
		UPtr<Shader> shader = MUPtr<Shader>(src, type, errorDest);
		if (!shader->IsValid())return -1;
		m_ShaderList.push_back(std::move(shader));
		return (S32)m_ShaderList.size() - 1;
	}

	S32 DX12Wrapper::DeleteShader(const S32 id)
	{
		if (OUT_OF_RANGE(m_ShaderList, id))return -1;
		if (m_ShaderList.at(id) == nullptr)return -1;
		auto& shader = m_ShaderList.at(id);
		if (0 < shader.use_count())return -1;
		shader.reset();
		return 0;
	}



	S32 DX12Wrapper::CreateGraphicPipeline(const GraphicPipelineDesc& desc)
	{
		InnerGraphicPipelineDesc iDesc(desc);


		#define CHECK_SHADER(stage) (!OUT_OF_RANGE(m_ShaderList, desc.##stage) &&m_ShaderList[desc.##stage])

		if (CHECK_SHADER(vs))iDesc.vsBolb = m_ShaderList.at(desc.vs)->GetShaderBolb();
		if (CHECK_SHADER(ps))iDesc.psBolb = m_ShaderList.at(desc.ps)->GetShaderBolb();
		if (CHECK_SHADER(gs))iDesc.gsBolb = m_ShaderList.at(desc.gs)->GetShaderBolb();
		if (CHECK_SHADER(hs))iDesc.hsBolb = m_ShaderList.at(desc.hs)->GetShaderBolb();
		if (CHECK_SHADER(ds))iDesc.dsBolb = m_ShaderList.at(desc.ds)->GetShaderBolb();


		auto gpipeline = MSPtr<GraphicPipeline>(m_Dev, iDesc);
		if (!gpipeline->IsValid())
		{
			return -1;
		}

		m_PipelineList.push_back(gpipeline);
		return (S32)m_PipelineList.size() - 1;
	}

	S32 DX12Wrapper::DeleteGraphicPipeline(const S32 id)
	{
		if (OUT_OF_RANGE(m_PipelineList, id))return -1;
		if (!m_PipelineList.at(id))return -1;

		auto& pipeline = m_PipelineList.at(id);
		if (0 < pipeline.use_count()) return -1;

		pipeline.reset();
		return 0;
	}

	S32 DX12Wrapper::SetGraphicPipeline(const S32 id)
	{
		if (OUT_OF_RANGE(m_PipelineList, id))return -1;
		auto& gpipeline = m_PipelineList.at(id);
		if (!gpipeline)return -1;
		gpipeline->SetGraphicPipeline(m_CmdList);
		return 0;
	}

	const HashMap<String, ShaderVariableDesc>& DX12Wrapper::GetShaderParamList(const S32 graphicPipelineID)
	{
		static const HashMap<String, ShaderVariableDesc> emptyMap;
		if (OUT_OF_RANGE(m_PipelineList, graphicPipelineID))return emptyMap;

		auto& pipeline = m_PipelineList[graphicPipelineID];
		if (!pipeline)return emptyMap;

		return pipeline->GetShaderParamList();
	}


	S32 DX12Wrapper::CreateMaterial(const S32 id, const S32 mask)
	{
		if (OUT_OF_RANGE(m_PipelineList, id))return -1;

		// パイプラインが削除されていたら終了
		if (!m_PipelineList.at(id))return -1;

		// シェーダーパラメータの作成
		auto shaderParamSet = MUPtr<Material>(m_Dev, m_PipelineList.at(id), mask);
		if (!shaderParamSet->IsValid())return -1;

		m_MaterialList.push_back(std::move(shaderParamSet));
		return (S32)m_MaterialList.size() - 1;
	}

	S32 DX12Wrapper::DeleteMaterial(const S32 id)
	{
		if (OUT_OF_RANGE(m_MaterialList, id))return -1;
		auto& material = m_MaterialList.at(id);
		if (0 < material.use_count())return -1;

		material.reset();
		return 0;
	}

	S32 DX12Wrapper::SetMaterial(const S32 id)
	{
		if (OUT_OF_RANGE(m_MaterialList, id))return -1;
		auto& shaderParamSet = m_MaterialList[id];
		if (!shaderParamSet)return -1;

		shaderParamSet->SetMaterial(m_Dev, m_CmdList);
		return 0;
	}


	S32 DX12Wrapper::LockMaterial(const S32 materialID)
	{
		if (OUT_OF_RANGE(m_MaterialList, materialID))return -1;
		auto& mat = m_MaterialList[materialID];
		if (mat == nullptr)return -1;
		mat->Lock();
		return 0;
	}

	S32 DX12Wrapper::SetShaderFloat4Param(const S32 id, const String& name, const Vector4& value)
	{
		if (OUT_OF_RANGE(m_MaterialList, id))return -1;
		auto& shaderParamSet = m_MaterialList[id];

		shaderParamSet->SetFloat4Param(name, value);
		return 0;
	}



	S32 DX12Wrapper::CreateShape(const U32 stribeSize, const U32 dataSize, const Byte* data, const U32 indexNum, const U32* indicis)
	{
		auto shape = MSPtr<Shape>(m_Dev, stribeSize, dataSize, data, indexNum, indicis);

		if (shape->IsValid() == false)return -1;

		m_ShapeList.push_back(shape);

		return (S32)m_ShapeList.size() - 1;
	}


	S32 DX12Wrapper::DrawShape(const S32 id)
	{
		if (OUT_OF_RANGE(m_ShapeList, id))return -1;
		auto& shape = m_ShapeList.at(id);
		if (shape == nullptr)return -1;
		return shape->Draw(m_CmdList);
	}





	// ここからプライベート関数
	DXGI_FORMAT DX12Wrapper::ConvertTextureFormat(const TextureFormat format)const
	{
		switch (format)
		{
		case TextureFormat::RGBA32:		return DXGI_FORMAT_R32G32B32A32_FLOAT;//
		case TextureFormat::RGBA16:		return DXGI_FORMAT_R16G16B16A16_UNORM;
		case TextureFormat::RGBA8:		return DXGI_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::RG8:		return DXGI_FORMAT_R8G8_SNORM;
		case TextureFormat::R32:		return DXGI_FORMAT_R32_FLOAT;//
		case TextureFormat::R16:		return DXGI_FORMAT_R16_UNORM;
		case TextureFormat::R8:			return DXGI_FORMAT_R8_UNORM;
		case TextureFormat::Depth:		return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case TextureFormat::RGB565:		return DXGI_FORMAT_B5G6R5_UNORM;
		case TextureFormat::RGBA5551:	return DXGI_FORMAT_B5G5R5A1_UNORM;
		}
		return DXGI_FORMAT_UNKNOWN;
	}
}