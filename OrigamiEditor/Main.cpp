#include "DxLib.h"
#include "EngineCore.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// �Q�[���G���W���̏�����
	if (OrigamiEngine::EngineCore::GetInstance().Init() < 0)return -1;

	OrigamiEngine::EngineCore::GetInstance().Run();

	// �\�t�g�̏I��
	return 0;
}