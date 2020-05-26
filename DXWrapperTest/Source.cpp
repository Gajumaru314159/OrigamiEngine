#include <iostream>
#include <windows.h>

#include <random>

#include "DXWrapper.h"

using namespace std;

HMODULE dll;

bool LoadAPI(String path)
{
	dll = LoadLibraryA(path.c_str());
	if (dll == NULL)
	{
		return false;
	}

	FARPROC proc = GetProcAddress(dll, "CreateGraphicWrapper");
	if (proc == NULL)
	{
		return false;
	}

	typedef og::IGraphicWrapper* (WINAPI* TProc)();

	TProc CreateGraphicWrapper = reinterpret_cast<TProc>(proc);
	//gapi = UPtr<og::IGraphicWrapper>(CreateGraphicWrapper());

	return true;
}


//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
int main()
{

	/*
	if (LoadAPI(L"C:/My/Productions/C++/OrigamiEngine/Out/x64/Debug/DXWrapper.dll") == false)
	{
		cout << "DLL‚Ì“Ç‚Ýž‚ÝŽ¸”s" << endl;
		return 0;
	}*/ {

		UPtr<og::IGraphicWrapper> gapi;
		gapi = UPtr<og::IGraphicWrapper>(og::CreateGraphicWrapper());


		if (!gapi)
		{
			cout << "ƒ‰ƒbƒp[‚Ìì¬‚ÉŽ¸”s" << endl;
			return 0;
		}

		if (gapi->Init() != 0)
		{
			cout << "‰Šú‰»Ž¸”s" << endl;
			return 0;
		}
		/*
		String error;
		S32 shaderID = gapi->LoadShader(L"", og::ShaderType::VERTEX, error);

		og::GraphicPipelineDesc desc;
		desc.shader.VS = shaderID;
		S32 gpipeline = gapi->CreateGraphicPipeline(desc);

		auto paramSet = gpipeline->CreateShaderParamSet(0);

		paramSet->SetTexture();

		gapi->SetGraphicPipeline(gpipline);
		gapi->SetShaderParamSet(paramSet);


		auto ms = gapi->CreateGraph(1280, 720);
		*/

		S32 mat = gapi->CreateMaterial(0, -1);

		Matrix matrix;
		matrix.m[0][0] = 2;
		matrix.m[1][1] = -2;
		matrix.m[2][2] = 2;
		matrix.m[3][0] = -1;
		matrix.m[3][1] = 1;
		gapi->SetShaderMatrixParam(mat, TC("mat"), matrix);

		while (gapi->SwapScreen() == 0)
		{
			Vector4 col(1, 1, 1, 1);
			col.w = 1;
			gapi->SetShaderFloat4Param(mat, TC("col"), col);
			//mg->DrawRect(0, 0, 32, 32, Color(1, 1, 1));

			gapi->SetGraphicPipeline(0);
			gapi->SetMaterial(mat);
			gapi->DrawShape(0);
		}
	}
	if (dll != nullptr)
	{
		FreeLibrary(dll);
	}
	return 0;
}