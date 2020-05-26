#include "pch.h"
#include "Rect.h"

namespace CommonLibrary
{
	Rect::Rect(F32 _x, F32 _y, F32 _width, F32 _height) :
		position(_x, _y),
		size(_width, _height)
	{
	};

	Rect::Rect() :Rect(0, 0, 100, 100) {};

	Rect::Rect(const Vector2& _position, const Vector2& _size) :position(_position), size(_size) {};
}