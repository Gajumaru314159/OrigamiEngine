#pragma once

#include <memory>
#include "IDXWrapper.h"

//#define DX12WRAPPER_EXPORTS
#ifdef DXWRAPPER_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

extern "C" {
	DLL OrigamiGraphic::IDXWrapper* CreateWrapper(OrigamiGraphic::DirectXVersion version);
}