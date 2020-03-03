/**
* @file UndefinedAsset.h
*/

#pragma once

#include "Prerequisites.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief �f�B���N�g���A�Z�b�g�B�q�v�f�Ƃ���EntryAsset���p�������N���X�̃I�u�W�F�N�g��ێ�����B
	*/
	class UndefinedAsset :public EntryAsset
	{
	public:
		/**
		* @brief �R���X�g���N�^�B
		*/
		UndefinedAsset(String path) :EntryAsset(path) {}
	};
}