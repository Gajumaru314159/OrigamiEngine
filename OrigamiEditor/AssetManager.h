/**
* @file AssetManager.h
*/

#pragma once

#include "OrigamiAPI.h"

#include "DirectoryAsset.h"

namespace OrigamiEngine {
	/**
	* @brief �e�N�X�`���⃂�f���Ȃǂ̃f�[�^�̓ǂݍ��݂Ǝ󂯓n�����s���B
	* @details �K��EnginCore�̏��������I����Ă���g�p���邱�ƁB
	*/
	class AssetManager:public Singleton<AssetManager> {
		friend class Singleton<AssetManager>;
	public:
		/**
		* @brief �w�肵���f�B���N�g���Ɋ܂܂��A�Z�b�g���ċA�I�ɐe�f�B���N�g���ɒǉ�����B
		* @param path	�A�Z�b�g�̓ǂݍ��݊J�n�n�_�̃f�B���N�g���̃p�X�B
		*/
		static void LoadAssets(const String path);


		/**
		* @brief ���[�g�f�B���N�g���̎擾�B
		*/
		static DirectoryAsset& GetRootDirectory();

		/**
		* @brief �A�Z�b�g�}�l�[�W���[�ŊǗ����ׂ��A�Z�b�g�̒ǉ�
		* @param asset	�ǉ�����A�Z�b�g
		* @return �A�Z�b�g�Ɍ��т���ꂽID
		*/
		static U32 AddAsset(SPtr<EntryAsset> asset);

	private:
		//! �G���W���ŕۗL���Ă���A�Z�b�g�ꗗ
		HashMap<U32, SPtr<EntryAsset>> m_AssetMap;

		//! �G�N�X�v���[���^�u��Assets�t�H���_�ɓ�����G���g��
		SPtr<DirectoryAsset> m_RootDir;
	};
}