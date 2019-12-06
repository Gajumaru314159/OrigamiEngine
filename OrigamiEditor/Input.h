#pragma once

#include "Prerequisites.h"



namespace OrigamiEngine {
	class Input :public Singleton<Input>
	{
		friend class Singleton<Input>;
	public:
		void Update();
		int GetMouseButtonPressedTime(const unsigned int num);


		static bool GetMouseHover(const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButton(const unsigned int num);
		static bool GetMouseButton(const unsigned int num, const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButtonDown(const unsigned int num);
		static bool GetMouseButtonDown(const unsigned int num, const int x1, const int y1, const int x2, const int y2);

		// GetAxis
		// GetButton
		// GetButtonDown
		// GetButtonUp
		// GetKey
		// GetKeyDown
		// GetKeyUp

	private:
		Input() :m_PressedTimes(8) {};
		ArrayList<int> m_PressedTimes;
	};
}