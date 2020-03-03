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
		enum class CursorType {
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
		S32 GetSystemColor(String id);

		/**
		* @brief マウスカーソルを変更する。
		*/
		void SetMouseCursor(const CursorType cursor);


		/**
		* @brief 文字列で指定してタブを開く。
		* @param tabName 開くタブの名前。
		* @return 指定したタブが存在しない場合はfalseを返す。
		*/
		static bool OpenTab(String tabName);


		/**
		* @brief 作成可能なタブの登録。
		* @param tabName タブの名前。
		* @param tab テンプレートとなるタブのインスタンス。
		*/
		static void ResisterTabTemplate(String tabName,UPtr<ITab> tab);

		//void RemoveTabTemplate(String tabName);
	private:
		// 作成可能なタブのマップ
		HashMap<String, UPtr<ITab>> m_TabMap;

		// 最上位のタブコンテナ。
		SplitContainer m_Container;

		// システムカラーのマップ
		HashMap<String, S32> m_ColorMap;

		// 次のフレームで設定するマウスカーソルの種類。
		CursorType m_NextCursor;

		// 現在のフレームのマウスカーソルの種類。
		CursorType m_CurrentCursor;

		// ウィドウに使用するテクスチャID。
		S32 m_WindowTex;

		/**
		* @brief コンストラクタ
		*/
		WindowManager();
	};

}