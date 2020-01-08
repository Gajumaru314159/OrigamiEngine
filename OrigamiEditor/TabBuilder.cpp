#include "DxLib.h"
#include "TabBuilder.h"

namespace OrigamiEngine {
	void TabBuilder::BeginDraw(F32 x, F32 y, F32 height, F32 width) {
		m_Rect.position.x = x;
		m_Rect.position.y = y;
		m_Rect.size.x = width;
		m_Rect.size.y = height;
		m_DrawPos = 0;
	}

	bool TabBuilder::PlaceButton(U32 color) {
		DrawBox(m_Rect.position.x+ m_DrawPos, m_Rect.position.y, m_Rect.position.x+32+ m_DrawPos, m_Rect.position.y + 32,color,TRUE);
		m_DrawPos += 34;
		return false;
	}
}