/**
* @file SystemManager.h
*/
#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine{
	/**
	* @brief システムマネージャ
	*/
	class SystemManager :public Singleton<SystemManager>
	{
		friend class Singleton<SystemManager>;
	public:
		static String GetProjectPath();
		static int FindFontHandle();
	private:
		String m_ProjectPath;
		HashMap<int, int> m_SystemFontMap;

		static SystemManager& GetInstance() {
			static SystemManager instance;
			return instance;
		}

		// TODO:プロジェクト名読み込み
		SystemManager();
	};
}