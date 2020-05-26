#pragma once

#include "Fwd.h"
#include "Vector2.h"

namespace CommonLibrary
{
	/// <summary>
	/// ��`�̈��\������N���X
	/// </summary>
	class DLL Rect
	{
	public:
		/// <summary>
		/// ���_����n�܂�傫��(100,100)�̋�`�̈�𐶐�����
		/// </summary>
		Rect();
		/// <summary>
		/// �V������`�̈�𐶐�����
		/// </summary>
		/// <param name="_x">��`�̎n�܂�x���W</param>
		/// <param name="_y">��`�̎n�܂�y���W</param>
		/// <param name="_width">��`�̉���</param>
		/// <param name="_height">��`�̍���</param>
		Rect(F32 _x, F32 _y, F32 _width, F32 _height);
		/// <summary>
		/// �V������`�̈���쐬����
		/// </summary>
		/// <param name="_position">��`�̎n�܂���W</param>
		/// <param name="_size">��`�̑傫��</param>
		Rect(const Vector2& _position, const Vector2& _size);

		//! ��`�̍�����W�B
		Vector2 position;

		//! ��`�̃T�C�Y
		Vector2 size;
	};
}