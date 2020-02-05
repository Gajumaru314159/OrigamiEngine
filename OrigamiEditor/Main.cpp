#include "DxLib.h"
#include "EngineCore.h"
#include "WindowManager.h"

#include "ITab.h"
S32 APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ S32 nShowCmd
){

	// ゲームエンジンの初期化
	if (OrigamiEngine::EngineCore::GetInstance().Init() < 0)return -1;
	

	HMODULE dll = LoadLibrary(L"C:/My/Productions/C++/OrigamiEngine/TabDLLTest/Out/bin/Debug/TabDLLTest.dll");
	if (dll == NULL)
	{
		return 0;
	}

	FARPROC proc = GetProcAddress(dll, "CreateTab");
	if (proc == NULL)
	{
		return 0;
	}

	typedef ITab* (WINAPI *TAddProc)();

	TAddProc add = reinterpret_cast<TAddProc>(proc);
	WindowManager::GetInstance().ResisterTabTemplate(L"T", UPtr<ITab>(add()));
	WindowManager::GetInstance().OpenTab(L"T");
	



	OrigamiEngine::EngineCore::GetInstance().Run();


	FreeLibrary(dll);

	// ソフトの終了
	return 0;
}