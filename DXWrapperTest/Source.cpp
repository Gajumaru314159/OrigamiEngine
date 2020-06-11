#include "DXWrapper.h"

#include <windows.h>

using namespace std;

UPtr<og::IGraphicWrapper> gapi;
HMODULE dll;
bool LoadAPI()
{
	dll = LoadLibraryA("DXWrapper.dll");
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

	{
		auto mat = gapi->CreateMaterial(0, -1);
		auto tex = gapi->LoadTexture(Path(TC("C:\\My\\Temp\\test.png")));

		auto shape = gapi->CreateShape(sizeof(F32) * 5);

		float m_Vertices[4*5];
		m_Vertices[0 * 5 + 0] = 0.0f;
		m_Vertices[0 * 5 + 1] = 0.0f;
		m_Vertices[0 * 5 + 2] = 0.0f;
		m_Vertices[0 * 5 + 3] = 0.0f;
		m_Vertices[0 * 5 + 4] = 0.0f;

		m_Vertices[1 * 5 + 0] = 1.0f;
		m_Vertices[1 * 5 + 1] = 0.0f;
		m_Vertices[1 * 5 + 2] = 0.0f;
		m_Vertices[1 * 5 + 3] = 1.0f;
		m_Vertices[1 * 5 + 4] = 0.0f;

		m_Vertices[2 * 5 + 0] = 0.0f;
		m_Vertices[2 * 5 + 1] = 1.0f;
		m_Vertices[2 * 5 + 2] = 0.0f;
		m_Vertices[2 * 5 + 3] = 0.0f;
		m_Vertices[2 * 5 + 4] = 1.0f;

		m_Vertices[3 * 5 + 0] = 1.0f;
		m_Vertices[3 * 5 + 1] = 1.0f;
		m_Vertices[3 * 5 + 2] = 0.0f;
		m_Vertices[3 * 5 + 3] = 1.0f;
		m_Vertices[3 * 5 + 4] = 1.0f;

		shape->Vertex((Byte*)m_Vertices,4);

		U32 indices[6] = { 0,1,2,2,1,3 };
		shape->Indices(indices,6);

		F32 t = 0;
		while (gapi->SwapScreen() == 0)
		{
			Vector4 col(1, 1, 0.5f + Mathf::Sin(2 * t) * 0.5f, 1);
			mat->SetFloat4Param(TC("col"), col);

			Matrix matrix;
			F32 scale = 200.0f;
			matrix.Rotate(0, 0, t);
			matrix.Scale(scale, scale, scale);
			matrix.Scale(1.0f / 1280, 1.0f / 720, 1);


			mat->SetMatrixParam(TC("mat"), matrix);

			mat->SetTexture(TC("tex"), tex);


			gapi->SetGraphicPipeline(0);
			gapi->SetMaterial(mat);
			gapi->DrawShape(shape);

			t += 0.02f;
		}
	}

	gapi.reset();
	FreeLibrary(dll);
	return 0;
}

