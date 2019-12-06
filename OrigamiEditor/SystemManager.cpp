#include "SystemManager.h"

#include "DxLib.h"

namespace OrigamiEngine {

	SystemManager::SystemManager():
		m_ProjectPath(L"C:\\My\\Productions\\OrigamiProject\\Test") {
		int handle=CreateFontToHandle(NULL, 10, -1);
		m_SystemFontMap.emplace(0, handle);



		// �W���̃t�H���g�w��
		SetFontThickness(1);
		SetFontSize(12);
	}

	String SystemManager::GetProjectPath() {
		return GetInstance().m_ProjectPath;
	}
}