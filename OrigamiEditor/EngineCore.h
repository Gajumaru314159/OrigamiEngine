/**
* @file EngineCore.h
*/
#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	/**
	* @brief �Q�[���G�f�B�^���N�����邽�߂̃N���X�B
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