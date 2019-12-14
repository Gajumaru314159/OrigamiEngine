#include "WindowManager.h"

#include <DxLib.h>

#include "TabContainer.h"
#include "EmptyTab.h"
#include "ExplorerTab.h"


namespace OrigamiEngine {
	WindowManager::WindowManager() :
		m_CurrentCursor(ARROW),
		m_NextCursor(ARROW),
		m_WindowTex(0)
	{
		// ウィンドウ関係のテクスチャを読み込み
		m_WindowTex = LoadGraph(L"Data/Textures/WindowTex.png");


		m_ColorMap.emplace(L"TabText", GetColor(255, 0, 0));

		auto sc1 = MUPtr<SplitContainer>();
		sc1->SetIsVertical(false);
		{
			auto tc11 = MUPtr<TabContainer>();
			{
				tc11->AddTab(MUPtr<EmptyTab>());
				tc11->AddTab(MUPtr<EmptyTab>());
			}
			auto tc12 = MUPtr<TabContainer>();
			{
				tc12->AddTab(MUPtr<EmptyTab>());
			}
			auto tc13 = MUPtr<TabContainer>();
			{
				tc13->AddTab(MUPtr<EmptyTab>());
			}
			sc1->AddContainer(std::move(tc11), 1.0f);
			sc1->AddContainer(std::move(tc12), 0.6f);
			sc1->AddContainer(std::move(tc13), 0.8f);
		}


		auto tc2 = MUPtr<TabContainer>();
		{
			tc2->AddTab(MUPtr<ExplorerTab>(m_WindowTex));
		}

		m_Container.AddContainer(std::move(tc2), 1.0f);
		m_Container.AddContainer(std::move(sc1), 0.6f);

		m_Container.SetIsVertical(true);
	}


	WindowManager::~WindowManager()
	{
	}

	void WindowManager::Update() {
		// 背景色を指定
		SetBackgroundColor(30, 30, 30);
		// 描画領域を画面全体にしてタブを描画
		int windowH, windowV;
		GetWindowSize(&windowH, &windowV);
		m_Container.Draw(3, 3, windowH - 6, windowV - 6);


		// マウスカーソルの変更
		static const auto arrow = LoadCursor(NULL, IDC_ARROW);
		static const auto hand = LoadCursor(NULL, IDC_HAND);
		static const auto sizens = LoadCursor(NULL, IDC_SIZENS);
		static const auto sizewe = LoadCursor(NULL, IDC_SIZEWE);
		
		//if (m_CurrentCursor != m_NextCursor) {
			switch (m_NextCursor) {
			case ARROW:
				SetCursor(arrow);
				break;
			case HAND:
				SetCursor(hand);
				break;
			case SIZENS:
				SetCursor(sizens);
				break;
			case SIZEWE:
				SetCursor(sizewe);
				break;
			}
			m_CurrentCursor = m_NextCursor;
		//}
		SetMouseCursor(ARROW);
	}

	int WindowManager::GetSystemColor(String key) {
		if (m_ColorMap.find(key) == m_ColorMap.end())return GetColor(0, 0, 0);
		return m_ColorMap[key];
	}




	void WindowManager::SetMouseCursor(const CURSOR cursor) {
		m_NextCursor = cursor;
	}
}