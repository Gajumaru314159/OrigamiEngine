#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class ITab {
	protected:
		virtual bool PlaceRepeatButton()=0;
		virtual void PlaceSpace()=0;
		virtual bool PlaceToggle()=0;
		virtual String PlaceTextField()=0;
		virtual String PlaceTextArea()=0;
	};
}