#include "pch.h"

#include "DX12Wrapper.h"
#include "DXWrapper.h"

namespace og
{
	IGraphicWrapper* CreateGraphicWrapper()
	{
		auto ptr = DX12Wrapper::Instance();
		//auto ptr = new DX12Wrapper();
		//singleton = UPtr<og::IGraphicWrapper>(ptr);
		return ptr;
	}
}