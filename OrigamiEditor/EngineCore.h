/**
* @file EngineCore.h
*/
#pragma once



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

		int Init();
		void Run();

	private:
		EngineCore();
		~EngineCore();
	};

}