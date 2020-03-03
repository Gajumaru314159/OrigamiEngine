/**
* @file Container.h
*/
#pragma once
#include "OrigamiAPI.h"
#include "ITab.h"



namespace OrigamiEngine {
	/**
	* @brief タブを保持することのできるコンテナ。
	*/
	class Container {
	public:
		virtual ~Container() {}

		/**
		* @brief コンテナの保持する子要素の数を取得する。
		* @return 子要素の数。
		*/
		virtual U32 GetChildCount() { return 0; };

		/**
		* @brief コンテナの描画。
		* @param x 描画位置X
		* @param y 描画位置Y
		* @param width 描画幅
		* @param height 描画高
		*/
		virtual void Draw(const S32 x, const S32 y, const S32 width, const S32 height)=0;

		virtual bool AddTab(ITab* tab, const U32 index = -1)=0;

		float GetPercentage();
		void SetPercentage(const float percentage);
	private:
		float m_Percentage = 0;
	};
}