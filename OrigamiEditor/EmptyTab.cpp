#include "EmptyTab.h"

namespace OrigamiEngine {

	EmptyTab::EmptyTab() {
		m_TabName = L"EmptyTab";
	}

	void EmptyTab::OnGUI(ITabBuilder& tabBuilder) {
		tabBuilder.PlaceButton(Color(1,0,0));
	}


	ITab* EmptyTab::CreateInstance() {
		return new EmptyTab();
	}


	void EmptyTab::Delete() {
		delete this;
	}
}