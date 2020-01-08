#include "DxLib.h"
#include "TabBuilder.h"

namespace OrigamiEngine {
	void TabBuilder::BeginDraw(S32 x, S32 y, S32 height, S32 width) {
		m_Rect.position.x = (F32)x;
		m_Rect.position.y = (F32)y;
		m_Rect.size.x = (F32)width;
		m_Rect.size.y = (F32)height;
		m_DrawPos = 0;
	}

	bool TabBuilder::PlaceButton(U32 color) {
		DrawBoxAA(m_Rect.position.x+ m_DrawPos, m_Rect.position.y, m_Rect.position.x+32+ m_DrawPos, m_Rect.position.y + 32,color,TRUE);
		m_DrawPos += 34;
		return false;
	}
}