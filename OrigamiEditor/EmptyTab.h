/**
* @file EmptyTab.h
*/
#pragma once

#include "ITab.h"


namespace OrigamiEngine {
	/**
	* @brief 何も表示しない空のタブ。
	*/
	class EmptyTab :public ITab {
	public:
		EmptyTab();

		virtual void OnGUI(ITabBuilder& tabBuilder);
	};
}