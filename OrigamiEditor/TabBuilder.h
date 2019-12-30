#pragma once

#include "OrigamiAPI.h"
#include "ITabBuilder.h"

namespace OrigamiEngine {
	class TabBuilder :public ITabBuilder, public Singleton<TabBuilder>
	{
		friend class Singleton<TabBuilder>;
	public:
		virtual void BeginDraw(F32 x, F32 y, F32 width, F32 height);

		virtual bool PlaceButton();
		/*virtual bool PlaceRepeatButton();
		virtual void PlaceSpace();
		virtual bool PlaceToggle();
		virtual String PlaceTextField();
		virtual String PlaceTextArea();*/
	private:
		Rect m_Rect;

		TabBuilder() {};
	};
}