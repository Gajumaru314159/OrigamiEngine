#include "DxLib.h"
#include "EngineCore.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// ゲームエンジンの初期化
	if (OrigamiEngine::EngineCore::GetInstance().Init() < 0)return -1;

	OrigamiEngine::EngineCore::GetInstance().Run();

	// ソフトの終了
	return 0;
}