#include "DxLib.h"
#include "EngineCore.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
){

	// �Q�[���G���W���̏�����
	if (OrigamiEngine::EngineCore::GetInstance().Init() < 0)return -1;

	OrigamiEngine::EngineCore::GetInstance().Run();

	// �\�t�g�̏I��
	return 0;
}