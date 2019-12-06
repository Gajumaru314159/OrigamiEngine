#include "Tab.h"

#include <DxLib.h>

#include "Input.h"

namespace OrigamiEngine {

	String Tab::GetTabName() {
		return m_TabName;
	}


	void Tab::SetRect(const I32 top, const I32 bottom, const I32 left, const I32 right)
	{
		m_TabRect.top = top;
		m_TabRect.bottom = bottom;
		m_TabRect.left = left;
		m_TabRect.right = right;

		m_Y = top;
	}

	bool Tab::PlaceButton()
	{
		DrawBox(0, m_Y, 32, m_Y + 30, GetColor(255, 255, 255), TRUE);
		DrawBox(0, m_Y, 32, m_Y + 30, GetColor(0,0,0), FALSE);
		m_Y += 32;

		return false;
	}
}