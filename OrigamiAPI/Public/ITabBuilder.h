#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class ITabBuilder {
	public:
		virtual void BeginDraw(S32 x, S32 y, S32 width, S32 height) = 0;
		virtual bool PlaceButton(const Color& color) = 0;
		/*virtual bool PlaceRepeatButton()=0;
		virtual void PlaceSpace()=0;
		virtual bool PlaceToggle()=0;
		virtual String PlaceTextField()=0;
		virtual String PlaceTextArea()=0;*/
	};
}