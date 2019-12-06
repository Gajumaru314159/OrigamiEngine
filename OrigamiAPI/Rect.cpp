#include "pch.h"
#include "Rect.h"

namespace OrigamiEngine {
	Rect::Rect(I32 _top, I32 _bottom, I32 _left, I32 _right) :
		top(_top),
		bottom(_bottom), 
		left(_left), 
		right(_right)
	{};

	Rect::Rect() :Rect(0, 0, 0, 0) {};

	/*I32 Rect::GetWidth()const
	{
		return right - left;
	}

	I32 Rect::GetHeight()const
	{
		return bottom - top;
	}*/
}