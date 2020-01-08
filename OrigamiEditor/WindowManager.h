/**
* @file WindowManager.h
*/

#pragma once

#include "Prerequisites.h"

#include "SplitContainer.h"
#include "ITab.h"



namespace OrigamiEngine {
	/**
	* @brief �G�f�B�^�̃^�u���Ǘ�����B
	*/
	class WindowManager :public Singleton<WindowManager>
	{
		friend class Singleton<WindowManager>;
	public:
		/**
		* @brief �}�E�X�J�[�\���̎�ށB
		*/
		enum CURSOR {
			ARROW,
			HAND,
			SIZENS,
			SIZEWE
		};


		/**
		* @brief �E�B���h�E�̍X�V�����B
		*/
		void Update();

		/**
		* @brief �V�X�e���J���[�̎擾
		* @param id �擾�������V�X�e���J���[�̖��O�B
		* @return �V�X�e���J���[�B
		*/
		int GetSystemColor(String id);

		/**
		* @brief �}�E�X�J�[�\����ύX����B
		*/
		void SetMouseCursor(const CURSOR cursor);


		/**
		* @brief ������Ŏw�肵�ă^�u���J���B
		* @param tabName �J���^�u�̖��O�B
		* @return �w�肵���^�u�����݂��Ȃ��ꍇ��false��Ԃ��B
		*/
		bool OpenTab(String tabName);


		/**
		* @brief �쐬�\�ȃ^�u�̓o�^�B
		* @param tabName �^�u�̖��O�B
		* @param tab �e���v���[�g�ƂȂ�^�u�̃C���X�^���X�B
		*/
		void ResisterTabTemplate(String tabName,UPtr<ITab> tab);

		//void RemoveTabTemplate(String tabName);

	protected:
		WindowManager();
	private:
		// �쐬�\�ȃ^�u�̃}�b�v
		HashMap<String, UPtr<ITab>> m_TabMap;

		// �ŏ�ʂ̃^�u�R���e�i�B
		SplitContainer m_Container;

		// �V�X�e���J���[�̃}�b�v
		HashMap<String, int> m_ColorMap;

		// ���̃t���[���Őݒ肷��}�E�X�J�[�\���̎�ށB
		CURSOR m_NextCursor;

		// ���݂̃t���[���̃}�E�X�J�[�\���̎�ށB
		CURSOR m_CurrentCursor;

		// �E�B�h�E�Ɏg�p����e�N�X�`��ID�B
		int m_WindowTex;
	};

}