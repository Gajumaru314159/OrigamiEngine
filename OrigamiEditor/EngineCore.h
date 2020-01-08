/**
* @file EngineCore.h
*/
#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	/**
	* @brief ゲームエディタを起動するためのクラス。
	*/
	class EngineCore
	{
	public:
		static EngineCore& GetInstance() {
			static EngineCore enginCore;
			return enginCore;
		}

		S32 Init();
		void Run();

	private:
		EngineCore();
		~EngineCore();
	};

}