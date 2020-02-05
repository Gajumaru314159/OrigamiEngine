/**
* @file EmptyTab.h
*/
#pragma once

#include "ITab.h"

namespace OrigamiEngine {
	/**
	* @brief �����\�����Ȃ���̃^�u�B
	*/
	class EmptyTab :public ITab {
	public:
		EmptyTab();

		void OnGUI(ITabBuilder& tabBuilder)override;
		ITab* CreateInstance()override;

		void Delete()override;
	};
}