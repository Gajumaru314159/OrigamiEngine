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
		static S32 FindFontHandle();
	private:
		String m_ProjectPath;
		HashMap<S32, S32> m_SystemFontMap;

		static SystemManager& GetInstance() {
			static SystemManager instance;
			return instance;
		}

		// TODO:プロジェクト名読み込み
		SystemManager();
	};
}