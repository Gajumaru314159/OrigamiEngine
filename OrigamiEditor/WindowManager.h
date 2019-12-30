/**
* @file WindowManager.h
*/

#pragma once

#include "Prerequisites.h"

#include "SplitContainer.h"
#include "ITab.h"



namespace OrigamiEngine {
	/**
	* @brief エディタのタブを管理する。
	*/
	class WindowManager :public Singleton<WindowManager>
	{
		friend class Singleton<WindowManager>;
	public:
		/**
		* @brief マウスカーソルの種類。
		*/
		enum CURSOR {
			ARROW,
			HAND,
			SIZENS,
			SIZEWE
		};


		/**
		* @brief ウィンドウの更新処理。
		*/
		void Update();

		/**
		* @brief システムカラーの取得
		* @param id 取得したいシステムカラーの名前。
		* @return システムカラー。
		*/
		int GetSystemColor(String id);

		/**
		* @brief マウスカーソルを変更する。
		*/
		void SetMouseCursor(const CURSOR cursor);
	protected:
		WindowManager();
	private:
		// 最上位のタブコンテナ。
		SplitContainer m_Container;
		// システムカラーのマップ
		HashMap<String, int> m_ColorMap;
		// 次のフレームで設定するマウスカーソルの種類。
		CURSOR m_NextCursor;
		// 現在のフレームのマウスカーソルの種類。
		CURSOR m_CurrentCursor;
		// ウィドウに使用するテクスチャID。
		int m_WindowTex;
		UPtr<ITab> m_FloatingTab;
	};

}