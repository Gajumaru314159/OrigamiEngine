#pragma once

#include <cstdarg>

namespace CommonLibrary
{
	inline bool CheckArgs(bool arg1 = true, bool arg2 = true, bool arg3 = true, bool arg4 = true)
	{
		if (arg1 == false)return true;
		if (arg2 == false)return true;
		if (arg3 == false)return true;
		if (arg4 == false)return true;
		return false;
	}
	/*
	template<class... A> bool CheckArgs(A... args)
	{
		for (bool isValid : std::initializer_list<bool>{ args... })
		{
			if (!isValid)return false;
		}
		return true;
	}*/
}