/**
* @file EngineCore.h
*/
#pragma once

#include "OrigamiAPI.h"
#include "WindowManager.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Input.h"

namespace OrigamiEngine {
	/**
	* @brief �Q�[���G�f�B�^���N�����邽�߂̃N���X�B
	*/
	class EngineCore:public Singleton<EngineCore>
	{
		friend class Singleton<EngineCore>;
	public:
		/**
		* @brief �Q�[���G���W���̋N���B
		* @details �������Ɏ��s���Ă����ꍇ�͒����ɏI������B
		*/
		static void Run();

	private:
		// �N�����ɏI�����邽�߂̃}�l�[�W���[�X�^�b�N
		Stack<void*> m_ManagerStack;

		WindowManager	*m_WindowManager;
		SystemManager	*m_SystemManager;
		AssetManager	*m_AssetManager;
		Input			*m_Input;

		EngineCore();
		~EngineCore();

		/**
		* @brief �Q�[���G���W���ŊǗ�����}�l�[�W����o�^����B
		* @details ���̊֐��ɓo�^���ꂽ�}�l�[�W���́A�G���W���I�����ɓo�^�Ƌt���ɉ�������B
		* @return �����ɓn�����}�l�[�W�����g�B
		*/
		template<class T>
		T* ResisterManager(T* manager);


		/**
		* @brief �Q�[���G���W���̏����������B
		* @return �������Ɏ��s�����ꍇ��false��Ԃ��B
		*/
		bool StartUp();
	};

}