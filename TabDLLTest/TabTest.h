// MathLibrary.h - Contains declarations of math functions
#pragma once

#include "ITab.h"

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

class DLLTab:public ITab {
public:
	DLLTab();
	void OnGUI(ITabBuilder& tabBuilder) override;
	ITab* CreateInstance()override;
};

extern "C" MATHLIBRARY_API ITab* CreateTab();