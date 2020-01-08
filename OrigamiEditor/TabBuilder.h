#pragma once

#include "OrigamiAPI.h"
#include "ITabBuilder.h"

namespace OrigamiEngine {
	class TabBuilder :public ITabBuilder, public Singleton<TabBuilder>
	{
		friend class Singleton<TabBuilder>;
	public:
		virtual void BeginDraw(S32 x, S32 y, S32 width, S32 height);

		virtual bool PlaceButton(U32 color);
		/*virtual bool PlaceRepeatButton();
		virtual void PlaceSpace();
		virtual bool PlaceToggle();
		virtual String PlaceTextField();
		virtual String PlaceTextArea();*/
	private:
		TabBuilder():m_DrawPos(0){}
		Rect m_Rect;
		S32 m_DrawPos;

	};
}