#include "DxLib.h"
#include "TabBuilder.h"

namespace OrigamiEngine {
	void TabBuilder::BeginDraw(F32 x, F32 y, F32 height, F32 width) {
		m_Rect.position.x = x;
		m_Rect.position.y = y;
		m_Rect.size.x = width;
		m_Rect.size.y = height;
	}

	bool TabBuilder::PlaceButton() {
		DrawBox(m_Rect.position.x, m_Rect.position.y, m_Rect.position.x+32, m_Rect.position.y + 32,GetColor(255,0,0),TRUE);
		return false;
	}
}