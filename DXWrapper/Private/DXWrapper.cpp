#include "pch.h"
#include "DXWrapper.h"
#include "DX12Wrapper.h"

using namespace OrigamiGraphic;

IDXWrapper* CreateWrapper(DirectXVersion version)
{
	switch (version)
	{
	case DirectXVersion::DX12:
		return new DX12Wrapper();
	default:
		break;
	}
	return nullptr;
}

int Test()
{
	return 0;
}