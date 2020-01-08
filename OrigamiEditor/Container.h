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

		virtual unsigned int GetChildCount() { return 0; };
		virtual void Draw(const F32 x, const F32 y, const F32 width, const F32 height)=0;
		virtual bool AddTab(ITab* tab, const U32 index = -1)=0;
		float GetPercentage();
		void SetPercentage(const float percentage);
	private:
		float m_Percentage = 0;
	};
}