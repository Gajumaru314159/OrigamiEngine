#pragma once

#include "Tab.h"



namespace OrigamiEngine {
	class EmptyTab :public Tab {
	public:
		EmptyTab();

		void OnGUI()override;
	};
}