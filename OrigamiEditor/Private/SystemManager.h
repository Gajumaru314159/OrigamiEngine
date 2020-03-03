/**
* @file SystemManager.h
*/
#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine{
	/**
	* @brief �V�X�e���}�l�[�W��
	*/
	class SystemManager :public Singleton<SystemManager>
	{
		friend class Singleton<SystemManager>;
	public:
		/**
		* @brief ���݊J���Ă���v���W�F�N�g�̊��t�H���_�̐�΃p�X���擾�B
		* @return �p�X�B
		*/
		Path GetProjectPath()const;

		/**
		* @brief ���݊J���Ă���v���W�F�N�g�̊��t�H���_�̐�΃p�X�̕�������擾�B
		* @return �p�X�B
		*/
		String GetProjectPathString()const;

		S32 FindFontHandle();
	private:
		// �v���W�F�N�g�̃p�X
		Path m_ProjectPath;
		// �V�X�e���̕`��Ŏg�p����t�H���g�̃}�b�v
		HashMap<S32, S32> m_SystemFontMap;

		// TODO:�v���W�F�N�g���ǂݍ���
		SystemManager();
	};
}