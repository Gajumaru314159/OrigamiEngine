#pragma once

#include "IGraphicWrapper.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace og
{
	class GLWrapper :public IGraphicWrapper
	{
	public:
		~GLWrapper();

		#pragma region
		// IGraphicWrapperの仮想関数の実装

		S32 Init() override;
		S32 SwapScreen() override;

		S32 LoadGraph(const String& path) override;



		S32 LoadShader(const String& path, ShaderType type, String& errorDest) override;
		S32 CreateShader(const String& path, ShaderType type, String& errorDest) override;
		S32 DeleteShader(const S32 id)override;


		S32 CreateGraphicPipeline(const GraphicPipelineDesc& desc)override;
		S32 DeleteGraphicPipeline(const S32 id) override;
		S32 SetGraphicPipeline(const S32 id) override;



		S32 CreateShaderParamSet(const S32 id, const S32 index)override;
		S32 DeleteShaderParamSet(const S32 id)override;
		S32 SetShaderParamSet(const S32 id)override;
		S32 SetShaderFloat4Param(const S32 id, const String& name, const Vector4& value)override;


		S32 CreateTexture(const S32 width, const S32 height, const TextureFormat format)override;



		S32 CreateVertexData(const U32 dataSIze, const U32 vertexCount)override;
		S32 SetVertexData(const S32 id, const Byte*)override;
		S32 CreateIndexData(const S32* indces, const S32 indexNum)override;

		#pragma endregion

	private:
		GLFWwindow* m_Window;


		ArrayList<GLuint> m_ShaderList;
	};
}