#include "DxLib.h"

#include "SystemManager.h"

namespace OrigamiEngine {

	SystemManager::SystemManager():
		m_ProjectPath(L"C:\\My\\Productions\\OrigamiProject\\Test") {
		S32 handle=CreateFontToHandle(NULL, 10, -1);
		m_SystemFontMap.emplace(0, handle);



		// 標準のフォント指定
		SetFontThickness(1);
		SetFontSize(12);
	}

	String SystemManager::GetProjectPath() {
		return GetInstance().m_ProjectPath;
	}
}