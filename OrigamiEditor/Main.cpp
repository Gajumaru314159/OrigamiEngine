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
	auto engine=OrigamiEngine::EngineCore::Create();
	
	// エンジンの起動
	engine->Run();
	engine->Destroy();

	// ソフトの終了
	return 0;
}