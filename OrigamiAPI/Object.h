/**
* @file Object.h
*/

#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief GC�ΏۂƂȂ���N���X
	* @details ���̃N���X���p�������N���X�͎����I��GC�ɓo�^����܂��B
	*/
	class Object {
	public:
		virtual ~Object()=0;
	};
}