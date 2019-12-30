#include "DxLib.h"
#include "EngineCore.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
){

	// ゲームエンジンの初期化
	if (OrigamiEngine::EngineCore::GetInstance().Init() < 0)return -1;

	OrigamiEngine::EngineCore::GetInstance().Run();

	// ソフトの終了
	return 0;
}