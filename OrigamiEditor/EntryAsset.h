/**
* @file EntryAsset.h
*/

#pragma once
#include <filesystem>

#include "OrigamiAPI.h"

#include "UUID.h"

namespace OrigamiEngine {

	class DirectoryAsset;

	/**
	* @brief �ǂݍ��݉\�ȃA�Z�b�g�̊��N���X
	*/
	class EntryAsset {
	public:
		/**
		* @brief �R���X�g���N�^�B�p�X���w�肷�邱�ƂőΏۂ̃A�Z�b�g��ǂݍ��ށB
		* @param path	�A�Z�b�g�̃p�X�B
		*/
		EntryAsset(String path);


		/**
		* @brief �A�Z�b�g�̃p�X���擾�B
		*/
		const String GetPath();

		/**
		* @brief �A�Z�b�g���̎擾�B
		*/
		const String GetName();
		/**
		* @brief �A�Z�b�g���̕ύX�B
		* @param name �V�������O�B
		*/
		void SetName(String name);

	protected:
		//! �A�Z�b�g�̃p�X�B
		Path m_Path;
	private:
		//! �A�Z�b�g�ŗL��ID�B
		UUID m_UUID;
	};
}