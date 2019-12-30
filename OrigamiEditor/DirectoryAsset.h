/**
* @file DirectoryAsset.h
*/

#pragma once

#include "OrigamiAPI.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief �f�B���N�g���A�Z�b�g�B�q�v�f�Ƃ���EntryAsset���p�������N���X�̃I�u�W�F�N�g��ێ�����B
	*/
	class DirectoryAsset :public EntryAsset {
	public:
		/**
		* @brief �w�肵���p�X���f�B���N�g���A�Z�b�g�Ƃ��ēǂݍ��ށB
		* @param path �ǂݍ��ރf�B���N�g���̃p�X�B
		*/
		DirectoryAsset(String path);


		/**
		* @brief �q�v�f�ɃA�Z�b�g��ǉ�����B
		* @param asset �ǉ�����A�Z�b�g
		*/
		void AddChild(SPtr<EntryAsset>& asset);

		/**
		* @brief �q�v�f�����X�g�Ŏ擾����B
		*/
		const ArrayList<SPtr<EntryAsset>>& GetChildren();

		/**
		* @brief ���̃f�B���N�g���ȉ��̃A�Z�b�g���ċA�I�ɓǂݍ��ށB
		*/
		void LoadChildEntries();

		/**
		* @brief �q�v�f�Ƀf�B���N�g�����܂ނ��ǂ����𒲂ׂ�B
		*/
		bool HasDirectory();
	private:
		// �q�v�f�̃��X�g
		ArrayList<SPtr<EntryAsset>> m_Children;
	};
}