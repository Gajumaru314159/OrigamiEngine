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

	if (!gapi)
	{
		FreeLibrary(dll);
		return false;
	}
	return true;
}

int main()
{
	//•ªŠòƒeƒXƒg
	//gapi = UPtr<og::IGraphicWrapper>(og::CreateGraphicWrapper());
	if (LoadAPI() == false)return 0;

	if (gapi->Init() != 0)return 0;

	{
		String errorDest;

		String vssrc;
		vssrc.append("\ncbuffer Data0 : register(b0) {matrix mat;};");
		vssrc.append("\nstruct Output {float4 pos:SV_POSITION;float2 uv:TEXCOORD;};");
		vssrc.append("\nOutput VSMain(float4 pos : POSITION ,float2 uv : TEXCOORD) {");
		vssrc.append("\n	 Output o;");
		vssrc.append("\n	 o.pos = mul(transpose(mat),pos);");
		vssrc.append("\n	 o.uv = pos.xy;");
		vssrc.append("\n	 return o;");
		vssrc.append("\n}");
		String pssrc;
		pssrc.append("\nTexture2D<float4> tex:register(t0);");
		pssrc.append("\nSamplerState smp:register(s0);");
		pssrc.append("\ncbuffer Data0 : register(b0) {matrix mat;};");
		pssrc.append("\ncbuffer Data1 : register(b1) {float4 col;};");
		pssrc.append("\nstruct Output {float4 pos:SV_POSITION;float2 uv:TEXCOORD;};");
		pssrc.append("\nfloat4 PSMain(Output i) : SV_TARGET{");
		pssrc.append("\n  return tex.Sample(smp,i.uv);");
		pssrc.append("\n}");

		og::GraphicPipelineDesc desc;

		desc.vs = gapi->CreateShader(vssrc, og::ShaderType::VERTEX, errorDest);
		desc.ps = gapi->CreateShader(pssrc, og::ShaderType::PIXEL, errorDest);
		desc.numRenderTargets = 1;
		auto gp = gapi->CreateGraphicPipeline(desc);




		auto mat = gapi->CreateMaterial(gp, -1);
		auto mat2 = gapi->CreateMaterial(gp, 1);
		auto tex = gapi->LoadTexture(Path(TC("test.png")));

		auto shape = gapi->CreateShape(sizeof(F32) * 5);
		float m_Vertices[8 * 5] = {
			0.0f,1.0f,0.0f,0.0f,0.0f,
			1.0f,1.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,1.0f,1.0f,//
			0.0f,1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,1.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,1.0f,1.0f,//
		};
		shape->Vertex((Byte*)m_Vertices, 4);

		U32 indices[12] = { 0,1,2,2,1,3,3,4,5,5,3,4 };
		shape->Indices(indices, 12);


		auto rt = gapi->CreateRenderTexture(1280, 720, og::TextureFormat::RGBA8);



		F32 t = 0;
		while (gapi->SwapScreen(rt) == 0)
		{
			Vector4 col(1, 1, 0.5f + Mathf::Sin(2 * t) * 0.5f, 1);

			F32 scale = 400.0f;
			Matrix matrix;
			matrix.Rotate(Quaternion(0, 0, Mathf::Radians(t)));
			matrix.Scale(scale, scale, scale);
			matrix.Scale(1.0f / 1280, 1.0f / 720, 1);

			mat->SetMatrixParam(TC("mat"), matrix);
			mat->SetTexture(TC("tex"), tex);



			rt->BeginDraw();

			rt->SetGraphicPipeline(gp);

			rt->SetMaterial(mat);
			rt->DrawInstanced(shape);




			Matrix matrix2;
			matrix2.Rotate(0, 0, -t);
			matrix2.Scale(scale, scale, scale);
			matrix2.Scale(1.0f / 1280, 1.0f / 720, 1);

			auto reds = mat2->SetMatrixParam(TC("mat"), matrix2);

			rt->SetMaterial(mat2);
			rt->DrawInstanced(shape);

			rt->EndDraw();

			t += 0.02f;
		}
	}

	gapi.reset();
	FreeLibrary(dll);
	return 0;
}

