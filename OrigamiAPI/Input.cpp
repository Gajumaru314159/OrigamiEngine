#include "pch.h"

#include "Input.h"

#include <DxLib.h>


namespace OrigamiEngine {

	void Input::Update()
	{
		int mouseInput = GetMouseInput();
		for (unsigned int i = 0; i < m_PressedTimes.size(); i++)
		{
			if (mouseInput & (1 << i))
			{
				m_PressedTimes[i]++;
			}
			else
			{
				m_PressedTimes[i] = 0;
			}
		}
	}


	int Input::GetMouseButtonPressedTime(const unsigned int num)
	{
		if (m_PressedTimes.size() <= num) return -1;
		return m_PressedTimes.at(num);
	}




	bool Input::GetMouseHover(const int x1, const int y1, const int x2, const int y2)
	{
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		// 描画エリア外は判定を除外する。
		RECT rect;
		GetDrawArea(&rect);
		if (mouseX < rect.left || rect.right <= mouseX || mouseY < rect.top || rect.bottom <= mouseY)
		{
			return false;
		}

		return (x1 <= mouseX && mouseX < x2 && y1 <= mouseY && mouseY < y2);
	}


	bool Input::GetMouseButton(const unsigned int num)
	{
		int MouseInput = GetMouseInput();
		return MouseInput & (1 << num);
	}
	bool Input::GetMouseButton(const unsigned int num, const int x1, const int y1, const int x2, const int y2)
	{
		return (GetMouseButton(num) && GetMouseHover(x1, y1, x2, y2));
	}

	bool Input::GetMouseButtonDown(const unsigned int num)
	{
		return GetInstance().GetMouseButtonPressedTime(num) == 1;
	}
	bool Input::GetMouseButtonDown(const unsigned int num, const int x1, const int y1, const int x2, const int y2)
	{
		return (GetMouseButtonDown(num) && GetMouseHover(x1, y1, x2, y2));
	}


	int Input::LEFT = 0;
	int Input::RIGHT = 1;
	int Input::MIDDLE = 2;

}