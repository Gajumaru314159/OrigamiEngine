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
		Container();
		virtual ~Container();

		virtual U32 GetChildCount() { return 0; };
		virtual void Draw(const S32 x, const S32 y, const S32 width, const S32 height)=0;
		virtual bool AddTab(ITab* tab, const U32 index = -1)=0;
		float GetPercentage();
		void SetPercentage(const float percentage);
	private:
		float m_Percentage = 0;
	};
}