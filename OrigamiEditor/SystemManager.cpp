#include "DxLib.h"

#include "SystemManager.h"

namespace OrigamiEngine {

	SystemManager::SystemManager():
		m_ProjectPath(L"C:\\My\\Productions\\OrigamiProject\\Test")
	{
		S32 handle=CreateFontToHandle(NULL, 10, -1);
		m_SystemFontMap.emplace(0, handle);



		// �W���̃t�H���g�w��
		SetFontThickness(1);
		SetFontSize(12);
	}

	Path SystemManager::GetProjectPath()const {
		return m_ProjectPath;
	}

	String SystemManager::GetProjectPathString()const {
		return String(m_ProjectPath);
	}

	S32 SystemManager::FindFontHandle(){
		return 0;
	}
}