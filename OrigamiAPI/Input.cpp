#include "pch.h"

#include "Input.h"

#include <DxLib.h>


namespace OrigamiEngine {

	void Input::Update()
	{
		S32 mouseInput = GetMouseInput();
		for (U32 i = 0; i < m_PressedTimes.size(); i++)
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


	S32 Input::GetMouseButtonPressedTime(const U32 num)
	{
		if (m_PressedTimes.size() <= num) return -1;
		return m_PressedTimes.at(num);
	}




	bool Input::GetMouseHover(const S32 x1, const S32 y1, const S32 x2, const S32 y2)
	{
		S32 mouseX, mouseY;
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


	bool Input::GetMouseButton(const U32 num)
	{
		S32 MouseInput = GetMouseInput();
		return MouseInput & (1 << num);
	}
	bool Input::GetMouseButton(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2)
	{
		return (GetMouseButton(num) && GetMouseHover(x1, y1, x2, y2));
	}

	bool Input::GetMouseButtonDown(const U32 num)
	{
		return GetInstance().GetMouseButtonPressedTime(num) == 1;
	}
	bool Input::GetMouseButtonDown(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2)
	{
		return (GetMouseButtonDown(num) && GetMouseHover(x1, y1, x2, y2));
	}


	S32 Input::LEFT = 0;
	S32 Input::RIGHT = 1;
	S32 Input::MIDDLE = 2;

}