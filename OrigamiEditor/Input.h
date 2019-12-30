/**
* @file Input.h
*/
#pragma once

#include "OrigamiAPI.h"



namespace OrigamiEngine {
	/**
	* @brief ���̓V�X�e���̃}�l�[�W���B
	* @details �}�E�X�A�L�[�{�[�h�A�Q�[���p�b�h�̓��͂����m����B���͂ɕʖ������邱�Ƃɂ���ĕ����̓��͂��܂Ƃ߂Ĉ������Ƃ��ł���B
	*/
	class Input :public Singleton<Input>
	{
		friend class Singleton<Input>;
	public:
		//! @brief �}�E�X�̍��{�^���̔ԍ�
		static int LEFT;
		//! @brief �}�E�X�̉E�{�^���̔ԍ�
		static int RIGHT;
		//! @brief �}�E�X�̒��{�^���̔ԍ�
		static int MIDDLE;

		/**
		* @brief ���͂̍X�V�����B
		*/
		void Update();

		/**
		* @brief �w�肵���}�E�X�̃{�^���̉�����Ă��鎞�Ԃ��擾����B
		* @param num �}�E�X�̃{�^���Ⓦ
		* @return ������Ă��鎞��(ms)
		*/
		int GetMouseButtonPressedTime(const unsigned int num);


		static bool GetMouseHover(const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButton(const unsigned int num);
		static bool GetMouseButton(const unsigned int num, const int x1, const int y1, const int x2, const int y2);
		static bool GetMouseButtonDown(const unsigned int num);
		static bool GetMouseButtonDown(const unsigned int num, const int x1, const int y1, const int x2, const int y2);

		// GetAxis
		// GetButton
		// GetButtonDown
		// GetButtonUp
		// GetKey
		// GetKeyDown
		// GetKeyUp

	private:
		Input() :m_PressedTimes(8) {};
		ArrayList<int> m_PressedTimes;
	};
}