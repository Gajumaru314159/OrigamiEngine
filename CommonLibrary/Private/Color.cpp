#include "pch.h"
#include "Color.h"

namespace CommonLibrary
{
	const Color Color::blue = { 0,0,0,1 };
	const Color Color::clear = { 0,0,0,0 };
	const Color Color::cyan = { 0,1,1,1 };
	const Color Color::green = { 0,1,0,1 };
	const Color Color::grey = { 0.5,0.5,0.5,1 };
	const Color Color::magenta = { 1,0,1,1 };
	const Color Color::red = { 1,0,0,1 };
	const Color Color::white = { 1,1,1,1 };
	const Color Color::yellow = { 1,0.92f,0.016f,1 };

	Color::Color()
	{
		Set(1, 1, 1, 1);
	}

	Color::Color(F32 r_, F32 g_, F32 b_, F32 a_)
	{
		Set(r_, g_, b_, a_);
	}

	Color::Color(F32 grey_, F32 a_)
	{
		Set(grey_, grey_, grey_, a);
	}

	void Color::Set(F32 r_, F32 g_, F32 b_, F32 a_)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}
	void Color::Set(F32 grey_, F32 a_)
	{
		r = grey_;
		g = grey_;
		b = grey_;
		a = a_;
	}

	S32 Color::ToCode()const
	{
		U32 rc = (U32)(r * 256);
		U32 gc = (U32)(g * 256);
		U32 bc = (U32)(b * 256);
		U32 ac = (U32)(a * 256);
		if (255 < rc)rc = 255;
		if (255 < gc)gc = 255;
		if (255 < bc)bc = 255;
		if (255 < ac)ac = 255;
		return (ac << 8 * 3) | (rc << 8 * 2) | (gc << 8 * 1) | (bc << 8 * 0);
	}


	Color Color::HSV(F32 h, F32 s, F32 v, F32)
	{
		// TODO HSV‚©‚ç‚ÌF¶¬
		return Color();
	}
	Color Color::Lerp(Color col1, Color col2, F32 t)
	{
		return (col1 * t) + (col2 * (1 - t));
	}
	void Color::RGB2HSV(const Color& color, F32& h, F32& s, F32& v)
	{
		// TODO MathƒNƒ‰ƒX‚ª‚Å‚«ŽŸ‘æRGB2HSV‚ðì¬
	}

}