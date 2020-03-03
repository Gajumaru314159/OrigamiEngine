/**
* @file GUISkin.h
*/

#pragma once

#include "Prerequisites.h"

#include "GUIMonoSkin.h"

namespace OrigamiEngine::GUILayout {
	struct
	{
		//! 通常時のスキン
		GUIMonoSkin normal;

		//! マウスホバー時のスキン
		GUIMonoSkin hover;

		//! フォーカスされているときのスキン
		GUIMonoSkin focus;

		//! マウスで押されているときのスキン
		GUIMonoSkin pressed;

		// 余白
		S32 margin;
	};
}