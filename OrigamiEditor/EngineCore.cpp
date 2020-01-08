#include "EngineCore.h"

#include <DxLib.h>

#include "WindowManager.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Input.h"


namespace OrigamiEngine {

	EngineCore::EngineCore()
	{
	}

	EngineCore::~EngineCore()
	{
		// ＤＸライブラリの後始末
		DxLib_End();
	}

	S32 EngineCore::Init() {


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
		if (DxLib_Init() < 0) return -1;


		// 描画先を裏画面へ設定
		SetDrawScreen(DX_SCREEN_BACK);

		// アセットの読み込み
		AssetManager::GetInstance().LoadAssets(SystemManager::GetProjectPath() + L"\\Assets");
		return 0;
	}



	void EngineCore::Run() {
		// メインループ
		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			Input::GetInstance().Update();
			WindowManager::GetInstance().Update();
		}
	}
}