#pragma once

#include "Fwd.h"
#include "Vector2.h"

namespace CommonLibrary
{
	/**
	* @brief ��`�̈��\������N���X�B
	*/
	class DLL Rect
	{
	public:
		Rect();
		Rect(F32 _x, F32 _y, F32 _width, F32 _height);

		//! ��`�̍�����W�B
		Vector2 position;

		//! ��`�̃T�C�Y
		Vector2 size;
	};
}