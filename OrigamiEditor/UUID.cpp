#include "UUID.h"

#include "Random.h"

namespace OrigamiEngine {

	UUID::UUID()
	{
		a = Random::GetU32();
		b = Random::GetU32();
		c = Random::GetU32();
		d = Random::GetU32();
	}

	UUID::UUID(String str)
	{

	}

	/**
	* @brief データを文字列として取り出す。"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"形式
	* @return String形式のUUID
	*/
	String UUID::ToString()
	{
		wchar_t buffer[64] = {};
		swprintf_s(buffer,64, L"%8.X-%8.X-%8.X-%8.X", a,b,c,d);
		return String(buffer);
	}

	// 比較演算子
	bool UUID::operator==(const UUID& an)
	{
		return
			a == an.a &&
			b == an.b &&
			c == an.c &&
			d == an.d;
	}

	bool UUID::operator!=(const UUID& an)
	{
		return
			a != an.a ||
			b != an.b ||
			c != an.c ||
			d != an.d;
	}
}
