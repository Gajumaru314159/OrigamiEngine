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

		virtual void OnGUI(ITabBuilder& tabBuilder);
	};
}