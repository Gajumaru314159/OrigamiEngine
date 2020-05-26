#pragma once

#include "Fwd.h"
#include "CustomString.h"

namespace CommonLibrary
{
	/// <summary>
	/// �t�@�C���܂��̓f�B���N�g���̃p�X�����i�[����
	/// </summary>
	class DLL Path
	{
	public:
		/// <summary>
		/// �p�X�I�u�W�F�N�g�̐���
		/// </summary>
		/// <param name="path">�p�X������</param>
		Path(const String& path);

		/// <summary>
		/// �����̃p�X��j�����ĐV�����p�X�����蓖�Ă�
		/// </summary>
		/// <param name="path">�p�X������</param>
		/// <returns></returns>
		S32 Set(const String& path);

		/// <summary>
		/// �p�X�I�u�W�F�N�g����t�@�C�������擾����
		/// </summary>
		/// <returns>�t�@�C�����܂��̓f�B���N�g����</returns>
		String FileName()const;

		/// <summary>
		/// �p�X�I�u�W�F�N�g����t�@�C���̊g���q���擾����
		/// </summary>
		/// <returns>�t�@�C���̊g���q�B�f�B���N�g����g���q�̂Ȃ��t�@�C���̏ꍇ�͂��當�����Ԃ��B</returns>
		String Extension()const;

		/// <summary>
		/// �p�X�I�u�W�F�N�g���g���q���܂ނ��ǂ����𔻒肷��
		/// </summary>
		/// <returns>�p�X�I�u�W�F�N�g���g���q���܂ނȂ�true��Ԃ�</returns>
		bool HasExtention()const;

		/// <summary>
		/// �p�X�I�u�W�F�N�g����t���p�X���擾����
		/// </summary>
		/// <returns>�t���p�X</returns>
		String Fullpath()const;

		/// <summary>
		/// �t�@�C�����܂�ł���f�B���N�g���̃p�X���擾����
		/// </summary>
		/// <returns>�f�B���N�g���̃p�X</returns>
		String Directory()const;

		/// <summary>
		/// �p�X���K�؂Ŋ܂ނ��Ƃ̂ł��Ȃ��������܂�ł��Ȃ���
		/// </summary>
		/// <returns></returns>
		inline bool IsValid()const { return m_Path.size() != 0; };

		/// <summary>
		/// �p�X�I�u�W�F�N�g��String�^�ɕϊ�����
		/// </summary>
		/// <returns></returns>
		const String& ToString() const { return m_Path; }
	private:
		String m_Path;
		bool m_HasExtention;
	};
}