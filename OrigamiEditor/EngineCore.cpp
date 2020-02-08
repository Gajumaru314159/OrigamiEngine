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
		// マネージャの削除
		while (!m_ManagerStack.empty()) {
			delete m_ManagerStack.top();
			m_ManagerStack.pop();
		}

		FreeLibrary(dll);

		// ＤＸライブラリの終了処理
		DxLib_End();
	}


	void EngineCore::Run() {
		// エンジンの初期化
		// 初期化に失敗したら直ちに終了する
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





		// メインループ
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			ms_Instance->m_Input->Update();
			ms_Instance->m_WindowManager->Update();
		}
	}


	bool EngineCore::StartUp()
	{
		// ウインドウモードで起動
		ChangeWindowMode(TRUE);
		// ウィンドウタイトルを変更
		SetWindowText(L"OrigamiEngine - TestScene.scene");

		// メニューを有効化
		AddMenuItem_Name(NULL, L"&File");
		AddMenuItem_Name(NULL, L"&Edit");
		AddMenuItem_Name(NULL, L"&Assets");
		AddMenuItem_Name(NULL, L"&GameObject");
		AddMenuItem_Name(NULL, L"&Component");
		AddMenuItem_Name(NULL, L"&Window");
		AddMenuItem_Name(NULL, L"&Help");
		AddMenuItem_Name(L"&File", L"New Scene(&N)");

		// 最大化ボタンが存在するウインドウモードに変更
		SetWindowStyleMode(8);

		// サイズ変更を可能にする
		SetWindowSizeChangeEnableFlag(TRUE, FALSE);


		//有効なデバイス数を取得
		S32 nDevs = DxLib::GetDirectDrawDeviceNum();
		S32 maxDesktopW = 0, maxDesktopH = 0;
		for (S32 i = nDevs - 1; 0 <= i; i--) {
			SetUseDirectDrawDeviceIndex(i);
			S32 DesktopW, DesktopH;
			GetDefaultState(&DesktopW, &DesktopH, NULL);
			maxDesktopW = max(maxDesktopW, DesktopW);
			maxDesktopH = max(maxDesktopH, DesktopH);
		}
		// 画面サイズをデスクトップのサイズと同じにする
		SetGraphMode(maxDesktopW, maxDesktopH, 32);


		// ウィンドウの最小サイズを設定
		SetWindowMinSize(950, 600);


		// ＤＸライブラリの初期化
		if (DxLib_Init() < 0) return false;


		// 描画先を裏画面へ設定
		SetDrawScreen(DX_SCREEN_BACK);


		// マネージャの登録
		// 登録した逆順に解放される
		m_WindowManager = ResisterManager<WindowManager>(WindowManager::Create());
		m_SystemManager = ResisterManager<SystemManager>(SystemManager::Create());
		m_AssetManager  = ResisterManager<AssetManager>(AssetManager::Create());
		m_Input			= ResisterManager<Input>(Input::Create());


		// アセットの読み込み
		m_AssetManager->LoadAssets(String(m_SystemManager->GetProjectPath()) + L"\\Assets");

		return true;
	}


	template<class T>
	T* EngineCore::ResisterManager(T* manager) {
		m_ManagerStack.push(manager);
		return manager;
	}
}