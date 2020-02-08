/**
* @file Path.h
*/

#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief �t�@�C���܂��̓f�B���N�g���̃p�X�����i�[����B
	*/
	class Path {
	public:
		/**
		* @brief �p�X�I�u�W�F�N�g�̐����B
		* @param path �p�X������B
		*/
		Path(String path);

		/**
		* @brief �����̃p�X��j�����ĐV�����p�X�����蓖�Ă�B
		* @param path �p�X������B
		*/
		void Set(String path);

		/**
		* @brief �p�X�I�u�W�F�N�g����t�@�C�������擾����B
		* @return �t�@�C�����܂��̓f�B���N�g�����B
		*/
		String FileName();

		/**
		* @brief �p�X�I�u�W�F�N�g����t�@�C���̊g���q���擾����B
		* @return �t�@�C���̊g���q�B�f�B���N�g����g���q�̂Ȃ��t�@�C���̏ꍇ�͂��當�����Ԃ��B
		*/
		String Extension();

		/**
		* @brief �p�X�I�u�W�F�N�g���g���q���܂ނ��ǂ����𔻒肷��B
		* @return �p�X�I�u�W�F�N�g���g���q���܂ނȂ�true��Ԃ��B
		*/
		bool HasExtention();

		/**
		* @brief �p�X�I�u�W�F�N�g����t���p�X���擾����B
		* @return �t���p�X�B
		*/
		String Fullpath();

		/**
		* @brief �t�@�C�����܂�ł���f�B���N�g���̃p�X���擾����B
		* @return �f�B���N�g���̃p�X�B
		*/
		String Directory();

		operator String() const { return m_Path; }
	private:
		String m_Path;
		bool m_HasExtention;
	};
}