/**
* @file DirectoryAsset.h
*/

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Prerequisites.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief �f�B���N�g���A�Z�b�g�B�q�v�f�Ƃ���EntryAsset���p�������N���X�̃I�u�W�F�N�g��ێ�����B
	*/
	class DirectoryAsset :public EntryAsset {
	public:
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
		void LoadChildEntries();

		/**
		* @brief �q�v�f�Ƀf�B���N�g�����܂ނ��ǂ���
		*/
		bool HasDirectory();
	private:
		// �T���l

		//! �q�v�f�̃��X�g
		ArrayList<SPtr<EntryAsset>> m_Children;
	};
}