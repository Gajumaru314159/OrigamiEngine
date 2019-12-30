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
	protected:
		WindowManager();
	private:
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
		UPtr<ITab> m_FloatingTab;
	};

}