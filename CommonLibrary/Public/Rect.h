#pragma once

#include "Fwd.h"
#include "Vector2.h"

namespace CommonLibrary
{
	/**
	* @brief 矩形領域を表現するクラス。
	*/
	class DLL Rect
	{
	public:
		Rect();
		Rect(F32 _x, F32 _y, F32 _width, F32 _height);

		//! 矩形の左上座標。
		Vector2 position;

		//! 矩形のサイズ
		Vector2 size;
	};
}