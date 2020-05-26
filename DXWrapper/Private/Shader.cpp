#include "pch.h"
#include "Shader.h"


#include <fstream>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


namespace
{
	static const char shaderEntryPoints[][16] =
	{
		"VSMain",
		"PSMain"
	};
	static const char shaderTargets[][16] =
	{
		"vs_5_0",
		"ps_5_0"
	};
}

namespace og
{
	Shader::Shader(const String& src, const ShaderType type, String& errorDest)
	{
		ComPtr<ID3DBlob> errorBlob = nullptr;
		auto result = D3DCompile(src.c_str(), src.size(), NULL, NULL, NULL,
								 shaderEntryPoints[(U32)type], shaderTargets[(U32)type],
								 D3DCOMPILE_PREFER_FLOW_CONTROL, 0, m_ShaderBolb.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());

		if (FAILED(result))
		{
			errorDest.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errorDest.begin());
			return;
		}
	}

	Shader::Shader(ComPtr<ID3DBlob>& bolb)
	{
		if (!bolb)return;

		m_ShaderBolb = bolb;
	}




	S32 Shader::GetShaderDataSize(ShaderParamType type)
	{
		switch (type)
		{
		case ShaderParamType::TEXTURE2D:return 0;
		case ShaderParamType::FLOAT4:return 4 * 4;
		case ShaderParamType::MATRIX:return 4 * 4 * 4;
		}
		return 0;
	}

	bool Shader::IsCompiledShader(const String& path)
	{
		std::FILE* fp;
		unsigned int id = -1;

		fopen_s(&fp, path.c_str(), "rb");
		if (fp == NULL)
		{
			return false;
		}

		std::fread(&id, sizeof(id), 1, fp);

		std::fclose(fp);

		return id == 0x43425844;
	}

	UPtr<Shader> Shader::LoadFromFile(const String& path, ShaderType type, String& errorDest)
	{
		if (IsCompiledShader(path))
		{
			ComPtr<ID3DBlob> bolb;

			//変換文字列格納バッファ
			WCHAR	wStrW[1024];

			size_t wLen = 0;

			//setlocale(LC_ALL, "japanese");

			mbstowcs_s(&wLen, wStrW, 1024, path.c_str(), _TRUNCATE);

			D3DReadFileToBlob(wStrW, bolb.ReleaseAndGetAddressOf());
			return MUPtr<Shader>(bolb);
		}

		std::ifstream ifs(path);
		std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		return MUPtr<Shader>(str, type, errorDest);
	}

}