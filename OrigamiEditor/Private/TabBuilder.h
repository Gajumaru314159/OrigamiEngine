#pragma once

#include "OrigamiAPI.h"
#include "ITabBuilder.h"

namespace OrigamiEngine {
	class TabBuilder :public ITabBuilder
	{
	public:
		TabBuilder() :m_DrawPos(0) {}

		void BeginDraw(S32 x, S32 y, S32 width, S32 height)override;

		bool PlaceButton(const Color& color)override;
		/*virtual bool PlaceRepeatButton();
		virtual void PlaceSpace();
		virtual bool PlaceToggle();
		virtual String PlaceTextField();
		virtual String PlaceTextArea();*/
	private:
		Rect m_Rect;
		S32 m_DrawPos;

	};
}