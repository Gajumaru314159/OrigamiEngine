#include "EngineCore.h"
#include <DxLib.h>
#include "WindowManager.h"
#include "Input.h"
#include "SystemManager.h"
#include "AssetManager.h"


namespace OrigamiEngine {

	EngineCore::EngineCore()
	{
	}

	EngineCore::~EngineCore()
	{
		// �c�w���C�u�����̌�n��
		DxLib_End();
	}

	int EngineCore::Init() {


		// �E�C���h�E���[�h�ŋN��
		ChangeWindowMode(TRUE);
		// �E�B���h�E�^�C�g����ύX
		SetWindowText(L"OrigamiEngine - TestScene.scene");

		// ���j���[��L����
		AddMenuItem_Name(NULL, L"&File");
		AddMenuItem_Name(NULL, L"&Edit");
		AddMenuItem_Name(NULL, L"&Assets");
		AddMenuItem_Name(NULL, L"&GameObject");
		AddMenuItem_Name(NULL, L"&Component");
		AddMenuItem_Name(NULL, L"&Window");
		AddMenuItem_Name(NULL, L"&Help");
		AddMenuItem_Name(L"&File", L"New Scene(&N)");

		// �ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX
		SetWindowStyleMode(8);

		// �T�C�Y�ύX���\�ɂ���
		SetWindowSizeChangeEnableFlag(TRUE, FALSE);


		//�L���ȃf�o�C�X�����擾
		int nDevs = DxLib::GetDirectDrawDeviceNum();
		int maxDesktopW = 0, maxDesktopH = 0;
		for (int i = nDevs - 1; 0 <= i; i--) {
			SetUseDirectDrawDeviceIndex(i);
			int DesktopW, DesktopH;
			GetDefaultState(&DesktopW, &DesktopH, NULL);
			maxDesktopW = max(maxDesktopW, DesktopW);
			maxDesktopH = max(maxDesktopH, DesktopH);
		}
		// ��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
		SetGraphMode(maxDesktopW, maxDesktopH, 32);


		// �E�B���h�E�̍ŏ��T�C�Y��ݒ�
		SetWindowMinSize(950, 600);


		// �c�w���C�u�����̏�����
		if (DxLib_Init() < 0) return -1;

		// �`���𗠉�ʂ֐ݒ�
		SetDrawScreen(DX_SCREEN_BACK);

		// �A�Z�b�g�̓ǂݍ���
		AssetManager::GetInstance().LoadAssets(SystemManager::GetProjectPath() + L"\\Assets");
		return 0;
	}



	void EngineCore::Run() {
		// ���C�����[�v
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			Input::GetInstance().Update();
			WindowManager::GetInstance().Update();
		}
	}
}