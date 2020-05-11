#include "IGraphicWrapper.h"

#ifdef GLWRAPPER_EXPORTS
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