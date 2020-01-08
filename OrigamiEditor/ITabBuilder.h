#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class ITabBuilder {
	public:
		virtual void BeginDraw(F32 x, F32 y, F32 width, F32 height) = 0;
		virtual bool PlaceButton(U32 color) = 0;
		/*virtual bool PlaceRepeatButton()=0;
		virtual void PlaceSpace()=0;
		virtual bool PlaceToggle()=0;
		virtual String PlaceTextField()=0;
		virtual String PlaceTextArea()=0;*/
	};
}