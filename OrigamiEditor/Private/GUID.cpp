#include "GUID.h"

namespace OrigamiEngine {

	GUID::GUID()
	{
		a = Random::GetU32();
		b = Random::GetU32();
		c = Random::GetU32();
		d = Random::GetU32();
	}

	GUID::GUID(String str)
	{

	}

	/**
	* @brief �f�[�^�𕶎���Ƃ��Ď��o���B"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"�`��
	* @return String�`����GUID
	*/
	String GUID::ToString()
	{
		wchar_t buffer[64] = {};
		swprintf_s(buffer,64, L"%8.X-%8.X-%8.X-%8.X", a,b,c,d);
		return String(buffer);
	}

	// ��r���Z�q
	bool GUID::operator==(const GUID& an)
	{
		return
			a == an.a &&
			b == an.b &&
			c == an.c &&
			d == an.d;
	}

	bool GUID::operator!=(const GUID& an)
	{
		return
			a != an.a ||
			b != an.b ||
			c != an.c ||
			d != an.d;
	}
}
