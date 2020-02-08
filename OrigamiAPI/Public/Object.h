/**
* @file Object.h
*/

#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief GC対象となる基底クラス
	* @details このクラスを継承したクラスは自動的にGCに登録されます。
	*/
	class Object {
	public:
		virtual ~Object()=0;
	};
}