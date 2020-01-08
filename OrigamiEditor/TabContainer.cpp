#include <DxLib.h>

#include "TabContainer.h"


#include "WindowManager.h"
#include "Input.h"

#include "EmptyTab.h"
#include "TabBuilder.h"

using namespace std;



namespace OrigamiEngine {

	TabContainer::~TabContainer() {

	}

	void TabContainer::Draw(const S32 x, const S32 y, const S32 width, const S32 height) {
		if (m_Tabs.empty())return;
		const S32 tabH = 22;

		S32 index = 0;
		S32 tabX = x;
		for (auto& tab : m_Tabs) {
			std::wstring tabNameString = tab->GetTabName();
			const wchar_t* tabName = tabNameString.c_str();
			S32 tabW = GetDrawStringWidth(tabName, (S32)wcslen(tabName)) + 16 + 20;// 文字幅+余白16+クローズボタン20

			// タブの描画
			if (index == m_ActiveIndex) {
				// 選択されているタブには背景を描画
				DrawBox(tabX, y, tabX + tabW, y + 2, GetColor(97, 171, 236), TRUE);
				DrawBox(tabX, y + 2, tabX + tabW, y + tabH - 1, GetColor(94, 94, 94), TRUE);
				DrawBox(tabX + 1, y + 2, tabX + tabW - 1, y + tabH - 1, GetColor(65, 65, 65), TRUE);

				DrawString(tabX + 8, y + 5, tabName, GetColor(200, 200, 200));
			}
			else {
				DrawString(tabX + 8, y + 5, tabName, GetColor(148, 148, 148));
			}

			// タブ切り替え
			if (Input::GetMouseHover(tabX, y, tabX + tabW, y + tabH)) {
				WindowManager::GetInstance().SetMouseCursor(WindowManager::HAND);
				if (Input::GetMouseButtonDown(0)) {
					m_ActiveIndex = index;
				}
			}


			tabX += tabW;
			index++;
		}

		// タブ背景の描画
		DrawBox(x, y + tabH, x + width, y + height, GetColor(65, 65, 65), TRUE);
		DrawBox(x, y + tabH, x + width, y + height, GetColor(94, 94, 94), FALSE);

		// タブコンテンツの描画
		TabBuilder::GetInstance().BeginDraw(x + 1, y + tabH + 1,  width - 2, height - 2);
		m_Tabs.at(m_ActiveIndex)->OnGUI(TabBuilder::GetInstance());
	}

	bool TabContainer::AddTab(ITab* tab, const U32 index) {
		if (index < 0 || m_Tabs.size() < index) {
			m_Tabs.emplace_back(UPtr<ITab>(tab));
		}
		else {
			m_Tabs.emplace(m_Tabs.begin() + index, UPtr<ITab>(tab));
		}
		return true;
	}
}