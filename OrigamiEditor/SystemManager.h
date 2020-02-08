/**
* @file SystemManager.h
*/
#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine{
	/**
	* @brief システムマネージャ
	*/
	class SystemManager :public Singleton<SystemManager>
	{
		friend class Singleton<SystemManager>;
	public:
		/**
		* @brief 現在開いているプロジェクトの基底フォルダの絶対パスを取得。
		* @return パス。
		*/
		Path GetProjectPath()const;

		/**
		* @brief 現在開いているプロジェクトの基底フォルダの絶対パスの文字列を取得。
		* @return パス。
		*/
		String GetProjectPathString()const;

		S32 FindFontHandle();
	private:
		// プロジェクトのパス
		Path m_ProjectPath;
		// システムの描画で使用するフォントのマップ
		HashMap<S32, S32> m_SystemFontMap;

		// TODO:プロジェクト名読み込み
		SystemManager();
	};
}