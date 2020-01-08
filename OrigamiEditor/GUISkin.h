/**
* @file GUISkin.h
*/

#pragma once

#include "Prerequisites.h"

#include "GUIMonoSkin.h"

namespace OrigamiEngine::GUILayout {
	struct
	{
		//! �ʏ펞�̃X�L��
		GUIMonoSkin normal;

		//! �}�E�X�z�o�[���̃X�L��
		GUIMonoSkin hover;

		//! �t�H�[�J�X����Ă���Ƃ��̃X�L��
		GUIMonoSkin focus;

		//! �}�E�X�ŉ�����Ă���Ƃ��̃X�L��
		GUIMonoSkin pressed;

		// �]��
		S32 margin;
	};
}