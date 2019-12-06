#pragma once



namespace OrigamiEngine {
	class EngineCore
	{
	public:
		EngineCore(const EngineCore&) = delete;
		EngineCore& operator=(const EngineCore&) = delete;
		EngineCore(EngineCore&&) = delete;
		EngineCore& operator=(EngineCore&&) = delete;

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