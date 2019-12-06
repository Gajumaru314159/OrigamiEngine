/**
* @file Rect.h
*/
#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief 矩形領域を表現するクラス。
	*/
	class Rect
	{
	public:
		Rect();
		Rect(I32 _top, I32 _bottom, I32 _left, I32 _right);

		//! 上座標。
		I32 top;
		//! 下座標。
		I32 bottom;
		//! 左座標。
		I32 left;
		//! 右座標。
		I32 right;


		/*I32 GetWidth()const;
		I32 GetHeight()const;*/
	};
}