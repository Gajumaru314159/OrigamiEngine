#include "EmptyTab.h"
#include "DxLib.h"

namespace OrigamiEngine {

	EmptyTab::EmptyTab() {
		m_TabName = L"EmptyTab";
	}

	void EmptyTab::OnGUI(ITabBuilder& tabBuilder) {
		tabBuilder.PlaceButton(GetColor(255,0,0));
	}


	ITab* EmptyTab::CreateInstance() {
		return new EmptyTab();
	}


	void EmptyTab::Delete() {
		delete this;
	}
}