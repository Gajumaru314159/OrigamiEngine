#include "Debug.h"

#include <windows.h>

#include <DxLib.h>



namespace OrigamiEngine {

	void Debug::ShowMessageBox(std::wstring text) {
		MessageBox(NULL, text.c_str(),
			L"ERROR", MB_ICONINFORMATION);
	}
}