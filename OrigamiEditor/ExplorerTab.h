#pragma once

#include "Tab.h"

#include "Prerequisites.h"

namespace OrigamiEngine {
	class ExplorerTab :public Tab {
	public:
		ExplorerTab(int windowTex);
		
		void OnGUI()override;
	private:
		static const int HIERARCHY_WIDTH_MIN = 100;
		int m_HierarchyWidth;
		int m_LeftArrowTex;
		int m_RightArrowTex;
		int m_FontHandle;
		int m_DirectoryTex;

		HashMap<String, bool> m_OpendFolderMap;

		U32 DrawHierarchy(const int x, const int y, const int width, const int height);
		void DrawAssets(const int x, const int y, const int width, const int height);
		void SetFontHandle(int handle);
	};
}

