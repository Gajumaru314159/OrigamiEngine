#include "pch.h"
#include "Random.h"

namespace OrigamiEngine {

	U32 Random::x = 123456789;
	U32 Random::y = 362436069;
	U32 Random::z = 521288629;
	U32 Random::w = 88675123;

	void Random::SetSeed(U32 seed)
	{
		do
		{
			seed = seed * 1812433253 + 1; seed ^= seed << 13; seed ^= seed >> 17;
			x = 123464980 ^ seed;
			seed = seed * 1812433253 + 1; seed ^= seed << 13; seed ^= seed >> 17;
			y = 3447902351 ^ seed;
			seed = seed * 1812433253 + 1; seed ^= seed << 13; seed ^= seed >> 17;
			z = 2859490775 ^ seed;
			seed = seed * 1812433253 + 1; seed ^= seed << 13; seed ^= seed >> 17;
			w = 47621719 ^ seed;
		} while (x == 0 && y == 0 && z == 0 && w == 0);
	}


	U32 Random::GetU32()
	{
		U32 t;
		t = x ^ (x << 11);
		x = y; y = z; z = w;
		w ^= t ^ (t >> 8) ^ (w >> 19);
		return w;
	}

	I32 Random::Range(I32 minimum, I32 maximum)
	{
		return GetU32() % (maximum - minimum) + minimum;
	}

	F32 Random::Range(F32 minimum, F32 maximum)
	{
		GetU32();
		return ((x + 0.5f) / 4294967296.0f + w) / 4294967296.0f;
	}
}