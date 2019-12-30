#include "EmptyTab.h"

namespace OrigamiEngine {

	EmptyTab::EmptyTab() {
		m_TabName = L"EmptyTab";
	}

	void EmptyTab::OnGUI(ITabBuilder& tabBuilder) {
		tabBuilder.PlaceButton();
	}
}