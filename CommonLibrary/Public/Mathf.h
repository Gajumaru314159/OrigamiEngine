#pragma once
#include "Fwd.h"

namespace CommonLibrary
{
	class Mathf
	{
	public:
		static const F32 PI;
		static const F32 TWO_PI;
		static const F32 EPSILON;
		static const F32 NAPIER;

	public:
		static inline F32 Abs(const F32 f) { return abs(f); }
		static inline F32 Acos(const F32 f) { return acos(f); }
		static inline bool Approximately(const F32 a, const F32 b) { return Abs(a - b) < EPSILON; }
		static inline F32 Asin(const F32 f) { return asin(f); }
		static inline F32 Atan(const F32 f) { return atan(f); }
		static inline F32 Atan2(const F32 y, const F32 x) { return atan2(y, x); }
		static inline F32 Ceil(const F32 f) { return ceil(f); }
		static inline F32 Clamp(const F32 f, const F32 min, const F32 max) { return Mathf::Max(Mathf::Min(f, max), min); }
		static inline F32 Clamp01(const F32 f) { return Mathf::Max(Mathf::Min(f, 1), 0); }
		static inline F32 Cos(const F32 f) { return cos(f); }
		static inline F32 BetweenAngle(const F32 to, const F32 from) { return abs(fmod(from - to, TWO_PI)); }
		static inline F32 Exp(const F32 f) { return exp(f); }
		static inline F32 Floor(const F32 f) { return floor(f); }
		static inline F32 Lerp(const F32 a, const F32 b, const F32 t) { return a * (1 - t) + b * t; }
		static inline F32 LerpAngle(const F32 a, const F32 b, const F32 t) { return fmod(a + fmod(b - a, TWO_PI) * t, TWO_PI); }
		static inline F32 InverseLerp(const F32 a, const F32 b, const F32 f) { return (b - a) / (f - a); }
		static inline F32 Log(const F32 f) { return log(f); }
		static inline F32 Log10(const F32 f) { return log10(f); }
		static inline F32 Max(const F32 a, const F32 b) { return a < b ? b : a; }
		static inline F32 Min(const F32 a, const F32 b) { return a < b ? a : b; }
		static inline F32 PingPong(const F32 f) { return abs(f * 0.5f - ceil(f * 0.5f) - 0.5f); }
		static inline F32 Pow(const F32 f, const F32 p) { return pow(f, p); }
		static inline F32 Round(const F32 f) { return round(f); }
		static inline F32 Sign(const F32 f) { if (f == 0.0f)return 0; return f / abs(f); }
		static inline F32 Sin(const F32 f) { return sin(f); }
		static inline F32 Sqrt(const F32 f) { return sqrt(f); }
		static inline F32 Tan(const F32 f) { return tan(f); }

		static inline F32 Degrees(const F32 f) { return f * 180.0f / PI; }
		static inline F32 Radians(const F32 f) { return f * PI / 180.0f; }


	};

	const F32 Mathf::PI = 3.14159265f;
	const F32 Mathf::TWO_PI = Mathf::PI * 2.0f;
	const F32 Mathf::EPSILON = FLT_EPSILON;
	const F32 Mathf::NAPIER = 2.71828182846f;
}