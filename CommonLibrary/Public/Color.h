#pragma once

#include "Fwd.h"

namespace CommonLibrary
{
	/// <summary>
	/// RGBAカラーを表現する構造体
	/// </summary>
	/// <remarks>
	/// 各色要素は、0〜1の範囲のF32型で表現されます。アルファ(a)を透過度を表し、0で完全な透明、1で完全な不透明を表します。
	/// </remarks>
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



		/// <summary> 赤成分 </summary>
		F32 r;
		/// <summary> 緑成分 </summary>
		F32 g;
		/// <summary> 青成分 </summary>
		F32 b;
		/// <summary> 透過成分 </summary>
		F32 a;

		/// <summary>
		/// 色を白(1,1,1,1)で初期化します
		/// </summary>
		Color();
		/// <summary>
		/// 各色成分を指定して初期化します
		/// </summary>
		/// <param name="r_">赤成分</param>
		/// <param name="g_">緑成分</param>
		/// <param name="b_">青成分</param>
		/// <param name="a_">透過成分</param>
		Color(F32 r_, F32 g_, F32 b_, F32 a_ = 1.0);
		/// <summary>
		/// 色成分を輝度で指定します
		/// </summary>
		/// <param name="grey_">輝度</param>
		/// <param name="a_">透過成分</param>
		Color(F32 grey_, F32 a_ = 1.0);

		/// <summary>
		/// 色成分を指定
		/// </summary>
		/// <param name="r_">赤成分</param>
		/// <param name="g_">緑成分</param>
		/// <param name="b_">青成分</param>
		/// <param name="a_">透過成分</param>
		void Set(F32 r_, F32 g_, F32 b_, F32 a_ = 1.0);
		/// <summary>
		/// 色成分を輝度で指定
		/// </summary>
		/// <param name="grey_">輝度</param>
		/// <param name="a_">透過成分</param>
		void Set(F32 grey_, F32 a_ = 1.0);
		/// <summary>
		/// 色をカラーコード表現で返す
		/// </summary>
		/// <returns>#AARRGGBB</returns>
		S32 ToCode()const;


		/// <summary>
		/// HSV色空間からRGB色を生成する
		/// </summary>
		/// <param name="h">色相</param>
		/// <param name="s">彩度</param>
		/// <param name="v">輝度</param>
		/// <param name="a">透過成分</param>
		/// <returns>色オブジェクト</returns>
		static Color HSV(F32 h, F32 s, F32 v, F32 a);

		/// <summary>
		/// t で col1 と col2 の色を線形補間する
		/// </summary>
		/// <remarks>
		/// tが0のときcol1を返し、tが1のときcol2を返す。
		/// </remarks>
		/// <param name="col1">色1</param>
		/// <param name="col2">色2</param>
		/// <param name="t">補完パラメーター</param>
		/// <returns>補完された色オブジェクト</returns>
		static Color Lerp(Color col1, Color col2, F32 t);

		/// <summary>
		/// RGBカラーをHSVに変換する
		/// </summary>
		/// <param name="color">変換元の色</param>
		/// <param name="h">色相出力先</param>
		/// <param name="s">彩度出力先</param>
		/// <param name="v">輝度出力先</param>
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