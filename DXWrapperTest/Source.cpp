#include "DXWrapper.h"

#include <windows.h>

using namespace std;

UPtr<og::IGraphicWrapper> gapi;
HMODULE dll;
bool LoadAPI()
{
	dll = LoadLibraryA("C:\\My\\Productions\\C++\\OrigamiEngine\\Out\\x64\\Debug\\DXWrapper.dll");
	if (dll == NULL)return false;

	FARPROC proc = GetProcAddress(dll, "CreateGraphicWrapper");
	if (proc == NULL)return false;

	typedef og::IGraphicWrapper* (*Func)();

	Func func = reinterpret_cast<Func>(proc);
	gapi = UPtr<og::IGraphicWrapper>(func());

	return true;
}

int main()
{
	//•ªŠòƒeƒXƒg
	//gapi = UPtr<og::IGraphicWrapper>(og::CreateGraphicWrapper());
	if (LoadAPI() == false)return 0;

	if (!gapi)return 0;
	if (gapi->Init() != 0)return 0;

	S32 mat = gapi->CreateMaterial(0, -1);
	S32 img = gapi->LoadGraph(TC("C:\\My\\Temp\\test.png"));

	F32 t = 0;
	while (gapi->SwapScreen() == 0)
	{
		Vector4 col(1, 1, 0.5f + Mathf::Sin(2 * t) * 0.5f, 1);
		gapi->SetShaderFloat4Param(mat, TC("col"), col);

		Matrix matrix;
		F32 scale = 200.0f;
		matrix.Rotate(0, 0, t);
		matrix.Scale(scale, scale, scale);
		matrix.Scale(1.0f / 1280, 1.0f / 720, 1);


		gapi->SetShaderMatrixParam(mat, TC("mat"), matrix);

		gapi->SetShaderTexture2DParam(mat, TC("tex"), img);


		gapi->SetGraphicPipeline(0);
		gapi->SetMaterial(mat);
		gapi->DrawShape(0);

		t += 0.02f;
	}
	return 0;
}

