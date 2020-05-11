#include "pch.h"

#include "GLWrapperMain.h"
#include "GLWrapper.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")

namespace og
{
	IGraphicWrapper* CreateGraphicWrapper()
	{
		auto ptr = new GLWrapper();
		return ptr;
	}


	GLWrapper::~GLWrapper()
	{
		if (m_Window != nullptr)
		{
			glfwDestroyWindow(m_Window);
		}
	}



	S32 GLWrapper::Init()
	{
		//glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);

		if (glfwInit() != GLFW_TRUE)
		{
			return -1;
		}


		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		m_Window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
		if (m_Window == nullptr)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_Window);

		// 垂直同期のタイミングを待つ
		glfwSwapInterval(1);

		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		return 0;
	}



	S32 GLWrapper::SwapScreen()
	{
		if (glfwWindowShouldClose(m_Window))
		{
			glfwTerminate();
			return -1;
		}
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(m_Window);
		glfwPollEvents();
		return 0;
	}

	S32 GLWrapper::LoadGraph(const String& path) { return 0; }



	S32 GLWrapper::GLWrapper::LoadShader(const String& path, ShaderType type, String& errorDest) { return 0; }
	S32 GLWrapper::GLWrapper::CreateShader(const String& src, ShaderType type, String& errorDest)
	{
		char* charSrc = new char[src.length() * MB_CUR_MAX + 1];
		size_t size;
		wcstombs_s(&size, charSrc, src.length() * MB_CUR_MAX + 1, src.c_str(), src.length() * MB_CUR_MAX + 1);



		const GLuint program(glCreateProgram());


		S32 gltype = 0;
		switch (type)
		{
		case og::ShaderType::VERTEX:gltype = GL_VERTEX_SHADER; break;
		case og::ShaderType::PIXEL:gltype = GL_FRAGMENT_SHADER; break;
		default:
			break;
		}

		const GLuint obj(glCreateShader(gltype));
		glShaderSource(obj, 1, &charSrc, NULL);
		glCompileShader(obj);





		glAttachShader(program, obj);
		glDeleteShader(obj);

		glBindAttribLocation(program, 0, "position");
		glBindFragDataLocation(program, 0, "fragment");
		glLinkProgram(program);




		GLint status;
		glGetShaderiv(program, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLsizei bufSize;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &bufSize);
			if (bufSize > 1)
			{
				// シェーダのコンパイル時のログの  内容を  取得する   
				std::vector<GLchar> infoLog(bufSize);
				GLsizei length;
				glGetShaderInfoLog(program, bufSize, &length, &infoLog[0]);



				//std::cerr << &infoLog[0] << std::endl;
			}
		}


		m_ShaderList.push_back(program);

		delete[] charSrc;
		return 0;
	}
	S32 GLWrapper::GLWrapper::DeleteShader(const S32 id) { return 0; }


	S32 GLWrapper::CreateGraphicPipeline(const GraphicPipelineDesc& desc) { return 0; }
	S32 GLWrapper::DeleteGraphicPipeline(const S32 id) { return 0; }
	S32 GLWrapper::SetGraphicPipeline(const S32 id) { return 0; }



	S32 GLWrapper::CreateShaderParamSet(const S32 id, const S32 index) { return 0; }
	S32 GLWrapper::DeleteShaderParamSet(const S32 id) { return 0; }
	S32 GLWrapper::SetShaderParamSet(const S32 id) { return 0; }
	S32 GLWrapper::SetShaderFloat4Param(const S32 id, const String& name, const Vector4& value) { return 0; }


	S32 GLWrapper::CreateTexture(const S32 width, const S32 height, const TextureFormat format) { return 0; }




	S32 GLWrapper::CreateVertexData(const U32 dataSIze, const U32 vertexCount) { return 0; }
	S32 GLWrapper::SetVertexData(const S32 id, const Byte*) { return 0; }
	S32 GLWrapper::CreateIndexData(const S32* indces, const S32 indexNum) { return 0; }
}