/**
* @file Rect.h
*/
#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief ��`�̈��\������N���X�B
	*/
	class Rect
	{
	public:
		Rect();
		Rect(I32 _top, I32 _bottom, I32 _left, I32 _right);

		//! ����W�B
		I32 top;
		//! �����W�B
		I32 bottom;
		//! �����W�B
		I32 left;
		//! �E���W�B
		I32 right;


		/*I32 GetWidth()const;
		I32 GetHeight()const;*/
	};
}