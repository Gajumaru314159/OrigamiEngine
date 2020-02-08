/**
* @file EngineCore.h
*/
#pragma once

#include "OrigamiAPI.h"
#include "WindowManager.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Input.h"

namespace OrigamiEngine {
	/**
	* @brief ゲームエディタを起動するためのクラス。
	*/
	class EngineCore:public Singleton<EngineCore>
	{
		friend class Singleton<EngineCore>;
	public:
		/**
		* @brief ゲームエンジンの起動。
		* @details 初期化に失敗していた場合は直ちに終了する。
		*/
		static void Run();

	private:
		// 起動順に終了するためのマネージャースタック
		Stack<void*> m_ManagerStack;

		WindowManager	*m_WindowManager;
		SystemManager	*m_SystemManager;
		AssetManager	*m_AssetManager;
		Input			*m_Input;

		EngineCore();
		~EngineCore();

		/**
		* @brief ゲームエンジンで管理するマネージャを登録する。
		* @details この関数に登録されたマネージャは、エンジン終了時に登録と逆順に解放される。
		* @return 引数に渡したマネージャ自身。
		*/
		template<class T>
		T* ResisterManager(T* manager);


		/**
		* @brief ゲームエンジンの初期化処理。
		* @return 初期化に失敗した場合はfalseを返す。
		*/
		bool StartUp();
	};

}