/**
* @file Input.h
*/
#pragma once

#include "Prerequisites.h"



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
		static S32 LEFT;
		//! @brief �}�E�X�̉E�{�^���̔ԍ�
		static S32 RIGHT;
		//! @brief �}�E�X�̒��{�^���̔ԍ�
		static S32 MIDDLE;

		/**
		* @brief ���͂̍X�V�����B
		*/
		void Update();

		/**
		* @brief �w�肵���}�E�X�̃{�^���̉�����Ă��鎞�Ԃ��擾����B
		* @param num �}�E�X�̃{�^���Ⓦ
		* @return ������Ă��鎞��(ms)
		*/
		S32 GetMouseButtonPressedTime(const U32 num);


		static bool GetMouseHover(const S32 x1, const S32 y1, const S32 x2, const S32 y2);
		static bool GetMouseButton(const U32 num);
		static bool GetMouseButton(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2);
		static bool GetMouseButtonDown(const U32 num);
		static bool GetMouseButtonDown(const U32 num, const S32 x1, const S32 y1, const S32 x2, const S32 y2);

		// GetAxis
		// GetButton
		// GetButtonDown
		// GetButtonUp
		// GetKey
		// GetKeyDown
		// GetKeyUp

	private:
		Input() :m_PressedTimes(8) {};
		ArrayList<S32> m_PressedTimes;
	};
}