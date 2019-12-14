#pragma once

#include "Prerequisites.h"

#include "SplitContainer.h"
#include "Tab.h"



namespace OrigamiEngine {
	class WindowManager :public Singleton<WindowManager>
	{
		friend class Singleton<WindowManager>;
	public:


		enum CURSOR {
			ARROW,
			HAND,
			SIZENS,
			SIZEWE
		};

		// ƒVƒ“ƒOƒ‹ƒgƒ“
		static WindowManager& GetInstance() {
			static WindowManager instance;
			return instance;
		}

		void Update();
		int GetSystemColor(String);
		void SetMouseCursor(const CURSOR cursor);
		//void SetFloatingTab(std::unique_ptr<Tab> tab);
		//std::unique_ptr<Tab> GetFloatingTab();
	private:
		SplitContainer m_Container;
		HashMap<String, int> m_ColorMap;
		CURSOR m_NextCursor;
		CURSOR m_CurrentCursor;
		UPtr<Tab> m_FloatingTab;
		int m_WindowTex;


		WindowManager();
		~WindowManager();
	};

}