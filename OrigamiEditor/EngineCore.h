/**
* @file EngineCore.h
*/
#pragma once



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

		int Init();
		void Run();

	private:
		EngineCore();
		~EngineCore();
	};

}