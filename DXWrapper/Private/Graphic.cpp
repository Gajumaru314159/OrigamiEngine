#include "pch.h"

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
		HRESULT result;
		ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;

		auto texture = MSPtr<RenderTexture>(ConvertTextureFormat(format), width, height);
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


	SPtr<IMaterial> DX12Wrapper::CreateMaterial(const SPtr<IGraphicPipeline>& pipeline, const S32 mask)
	{
		if (CheckArgs(!!pipeline))return nullptr;

		// シェーダーパラメータの作成
		auto material = MUPtr<Material>(pipeline, mask);
		if (material->IsValid() == false)return nullptr;

		return material;
	}

	SPtr<IShape> DX12Wrapper::CreateShape(const U32 stribeSize)
	{
		if (stribeSize <= 0)return nullptr;
		auto shape = MSPtr<Shape>(stribeSize);
		return shape;
	}


	//S32 DX12Wrapper::DrawShape(SPtr<IShape> shape)
	//{
	//	if (CheckArgs(!!shape))return -1;
	//	auto ptr = dynamic_cast<Shape*>(shape.get());
	//	return ptr->Draw(m_Dev, m_CmdList);
	//}

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