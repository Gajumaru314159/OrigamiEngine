/**
* @file Container.h
*/
#pragma once
#include "Container.h"



namespace OrigamiEngine {
	/**
	* @brief タブを保持することのできるコンテナ。
	*/
	class Container {
	public:
		Container();
		virtual ~Container();

		virtual unsigned int GetChildCount() { return 0; };
		virtual void Draw(const int x, const int y, const int width, const int height);
		float GetPercentage();
		void SetPercentage(const float percentage);
	private:
		float m_Percentage = 0;
	};
}