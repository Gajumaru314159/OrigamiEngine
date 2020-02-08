#include "EngineCore.h"

#include <DxLib.h>

#include "WindowManager.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Input.h"

namespace OrigamiEngine {
	HMODULE dll;
	EngineCore::EngineCore() :Singleton<EngineCore>(),
		m_WindowManager(nullptr),
		m_SystemManager(nullptr),
		m_AssetManager(nullptr),
		m_Input(nullptr)
	{

	}

	EngineCore::~EngineCore()
	{
		// �}�l�[�W���̍폜
		while (!m_ManagerStack.empty()) {
			delete m_ManagerStack.top();
			m_ManagerStack.pop();
		}

		FreeLibrary(dll);

		// �c�w���C�u�����̏I������
		DxLib_End();
	}


	void EngineCore::Run() {
		// �G���W���̏�����
		// �������Ɏ��s�����璼���ɏI������
		if (ms_Instance->StartUp() == false)return;





		dll = LoadLibrary(L"C:/My/Productions/C++/OrigamiEngine/TabDLLTest/Out/bin/Debug/TabDLLTest.dll");
		if (dll == NULL)
		{
			return;
		}

		FARPROC proc = GetProcAddress(dll, "CreateTab");
		if (proc == NULL)
		{
			return;
		}

		typedef ITab* (WINAPI* TAddProc)();

		TAddProc add = reinterpret_cast<TAddProc>(proc);
		WindowManager::ResisterTabTemplate(L"T", UPtr<ITab>(add()));
		WindowManager::OpenTab(L"T");





		// ���C�����[�v
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			ms_Instance->m_Input->Update();
			ms_Instance->m_WindowManager->Update();
		}
	}


	bool EngineCore::StartUp()
	{
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
		S32 nDevs = DxLib::GetDirectDrawDeviceNum();
		S32 maxDesktopW = 0, maxDesktopH = 0;
		for (S32 i = nDevs - 1; 0 <= i; i--) {
			SetUseDirectDrawDeviceIndex(i);
			S32 DesktopW, DesktopH;
			GetDefaultState(&DesktopW, &DesktopH, NULL);
			maxDesktopW = max(maxDesktopW, DesktopW);
			maxDesktopH = max(maxDesktopH, DesktopH);
		}
		// ��ʃT�C�Y���f�X�N�g�b�v�̃T�C�Y�Ɠ����ɂ���
		SetGraphMode(maxDesktopW, maxDesktopH, 32);


		// �E�B���h�E�̍ŏ��T�C�Y��ݒ�
		SetWindowMinSize(950, 600);


		// �c�w���C�u�����̏�����
		if (DxLib_Init() < 0) return false;


		// �`���𗠉�ʂ֐ݒ�
		SetDrawScreen(DX_SCREEN_BACK);


		// �}�l�[�W���̓o�^
		// �o�^�����t���ɉ�������
		m_WindowManager = ResisterManager<WindowManager>(WindowManager::Create());
		m_SystemManager = ResisterManager<SystemManager>(SystemManager::Create());
		m_AssetManager  = ResisterManager<AssetManager>(AssetManager::Create());
		m_Input			= ResisterManager<Input>(Input::Create());


		// �A�Z�b�g�̓ǂݍ���
		m_AssetManager->LoadAssets(String(m_SystemManager->GetProjectPath()) + L"\\Assets");

		return true;
	}


	template<class T>
	T* EngineCore::ResisterManager(T* manager) {
		m_ManagerStack.push(manager);
		return manager;
	}
}