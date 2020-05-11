#pragma once

#include "Fwd.h"

namespace CommonLibrary
{
	/**
	* @brief 色を扱うクラス。
	*/
	class DLL Color
	{
	public:
		//
		// 定数部
		//

		static const Color black;
		static const Color blue;
		static const Color clear;
		static const Color cyan;
		static const Color green;
		static const Color grey;
		static const Color magenta;
		static const Color red;
		static const Color white;
		static const Color yellow;



		//! @brief 赤成分
		F32 r;
		//! @brief 緑成分
		F32 g;
		//! @brief 青成分
		F32 b;
		//! @brief 透過度
		F32 a;

		Color();
		Color(F32 r_, F32 g_, F32 b_, F32 a_ = 1.0);
		Color(F32 grey_, F32 a_ = 1.0);

		void Set(F32 r_, F32 g_, F32 b_, F32 a_ = 1.0);
		void Set(F32 grey_, F32 a_ = 1.0);
		S32 ToCode()const;



		static Color HSV(F32 h, F32 s, F32 v);
		static Color Lerp(Color col1, Color col2, F32 t);
		static void RGB2HSV(const Color& color, F32& h, F32& s, F32& v);

		inline Color operator + (const Color& another) const
		{
			return Color(r + another.r, g + another.g, b + another.b, a);
		}

		inline Color operator - (const Color& another) const
		{
			return Color(r - another.r, g - another.g, b - another.b, a);
		}

		inline Color operator * (float f) const
		{
			return Color(r * f, g * f, b * f, a);
		}

		inline Color operator * (const Color& another) const
		{
			return Color(r * another.r, g * another.g, b * another.b, a);
		}

		inline Color operator / (float f) const
		{
			f = 1.0f / f;
			return Color(r * f, g * f, b * f, a);
		}

		inline Color& operator += (const Color& another)
		{
			r += another.r;
			g += another.g;
			b += another.b;

			return *this;
		}

		inline Color& operator -= (const Color& another)
		{
			r -= another.r;
			g -= another.g;
			b -= another.b;

			return *this;
		}

		inline Color& operator *= (float f)
		{
			r *= f;
			g *= f;
			b *= f;

			return *this;
		}

		inline Color& operator *= (Color& another)
		{
			r *= another.r;
			g *= another.g;
			b *= another.b;

			return *this;
		}
	};
}