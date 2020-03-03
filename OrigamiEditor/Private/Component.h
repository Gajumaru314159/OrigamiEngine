/**
* pfile Component.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine {
	namespace GUILayout {
		/**
		* @brief エディターのGUIを構成するコンポーネントのクラス。
		*/
		class Component
		{
		public:
			/**
			* @brief コンポーネント。
			*/
			Component();


			/**
			* @brief 描画と処理の更新。
			*/
			virtual void update() = 0;

			/**
			* @brief 描画と処理の更新を実行するかを設定。
			* @param flag フラグ。trueだと描画処理が有効になる。
			*/
			void SetEnable(bool flag);

			/**
			* @brief コンポーネントの最小サイズを設定。
			*/
			void SetMinimumSize(U32 width, U32 height);

			/**
			* @brief コンポーネントの最大サイズを設定。
			*/
			void SetMaximumSize(U32 width, U32 height);


			/**
			* @brief コンポーネントの横幅を取得。
			* @return コンポーネントの横幅。
			*/
			U32 GetWidth();

			/**
			* @brief コンポーネントの高さを取得。
			* @return コンポーネントの高さ。
			*/
			U32 GetHeight();
		private:
			// 描画処理が有効か
			bool m_IsEnable;

			// コンポーネントの横幅
			U32 m_Width;
			// コンポーネントの高さ
			U32 m_Height;

			// コンポーネントの最小の横幅
			U32 m_MinWidth;
			// コンポーネントの最小の高さ
			U32 m_MinHeight;

			// コンポーネントの最大の横幅
			U32 m_MaxWidth;
			// コンポーネントの最大の高さ
			U32 m_MaxHeight;
		};
	}
}