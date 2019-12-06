#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	class Tab
	{
	public:
		virtual void OnGUI()=0;

		String GetTabName();

		void SetRect(const I32 top, const I32 bottom, const I32 left, const I32 right);

		/*void BeginBox();
		void EndBox();*/
		bool PlaceButton();

		/**
		* @brief 指定したスキンのボタンを配置
		* @return ボタンが押されている間trueを返す
		*/
		/*bool PlaceRepeatButton();
		void PlaceSpace();
		bool PlaceToggle();
		String PlaceTextField();
		String PlaceTextArea();*/
		// スクロールバー

	protected:
		String m_TabName = L"No Name";
	private:
		Rect m_TabRect;
		I32 m_Y;
	};
}