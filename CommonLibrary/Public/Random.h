#pragma once

#include "Fwd.h"


namespace CommonLibrary
{
	/// <summary>
	/// ���������̂��߂̃N���X
	/// </summary>
	class DLL Random
	{
	public:
		/// <summary>
		/// �����̃V�[�h�l��ύX����
		/// </summary>
		/// <param name="seed">�V�[�h�l</param>
		static void SetSeed(U32 seed);

		/// <summary>
		/// 0����2^32�܂ł̐����̗����𐶐�����
		/// </summary>
		/// <returns>�������ꂽ����</returns>
		static U32 GetU32();

		/// <summary>
		/// �����̗����𐶐�����
		/// </summary>
		/// <remarks>
		/// minimum����maximum�̊Ԃ��痐���𐶐�����
		/// </remarks>
		/// <param name="minimum">�����̍ŏ��l</param>
		/// <param name="maximum">�����̍ő�l</param>
		/// <returns>minimum�ȏ�maximum�ȉ��̗���</returns>
		static S32 Range(S32 minimum, S32 maximum);

		/// <summary>
		/// �����̗����𐶐�����
		/// </summary>
		/// <remarks>
		/// minimum����maximum�̊Ԃ��痐���𐶐�����
		/// </remarks>
		/// <param name="minimum">�����̍ŏ��l</param>
		/// <param name="maximum">�����̍ő�l</param>
		/// <returns>minimum�ȏ�maximum�ȉ��̗���</returns>
		static F32 Range(F32 minimum, F32 maximum);
	};
}