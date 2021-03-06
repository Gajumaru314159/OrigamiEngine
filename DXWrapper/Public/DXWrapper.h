﻿#pragma once

#include "IGraphicWrapper.h"

#ifdef DXWRAPPER_EXPORTS
#define DLL_OG __declspec(dllexport)
#else
#define DLL_OG __declspec(dllimport)
#endif

namespace og
{
	extern "C" {
		DLL_OG IGraphicWrapper* CreateGraphicWrapper();
	}
}