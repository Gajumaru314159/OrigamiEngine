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

	// �Q�[���G���W���̏�����
	auto engine=OrigamiEngine::EngineCore::Create();
	
	// �G���W���̋N��
	engine->Run();
	engine->Destroy();

	// �\�t�g�̏I��
	return 0;
}