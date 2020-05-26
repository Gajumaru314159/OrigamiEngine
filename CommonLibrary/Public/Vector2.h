#pragma once

#include "Fwd.h"


namespace CommonLibrary
{
	/// <summary>
	/// 2次元ベクトルのクラス
	/// </summary>
	class DLL Vector2
	{
	public:
		/// <summary>ベクトルのx成分 </summary>
		F32 x;
		/// <summary>ベクトルのy成分 </summary>
		F32 y;


		/// <summary>
		/// 与えられたx,y成分から新しいベクトルを生成する
		/// </summary>
		/// <param name="_x">x成分</param>
		/// <param name="_y">y成分</param>
		Vector2(F32 _x, F32 _y) :x(_x), y(_y) {}
		Vector2() :Vector2(0, 0) {}


		inline Vector2& operator = (const Vector2& v)
		{
			x = v.x;
			y = v.y;

			return *this;
		}

		inline bool operator == (const Vector2& v) const
		{
			return (x == v.x && y == v.y);
		}

		inline bool operator != (const Vector2& v) const
		{
			return (x != v.x || y != v.y);
		}

		inline bool operator < (const Vector2& v) const
		{
			return (x < v.x&& y < v.y);
		}

		inline bool operator > (const Vector2& v) const
		{
			return (x > v.x && y > v.y);
		}

		inline Vector2 operator + (const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		inline Vector2 operator - (const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		inline Vector2 operator * (float f) const
		{
			return Vector2(x * f, y * f);
		}

		inline Vector2 operator * (const Vector2& v) const
		{
			return Vector2(x * v.x, y * v.y);
		}

		inline Vector2 operator / (float f) const
		{
			f = 1.0f / f;
			return Vector2(x * f, y * f);
		}

		inline Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		inline friend Vector2 operator * (float f, const Vector2& v)
		{
			return Vector2(f * v.x, f * v.y);
		}

		inline Vector2& operator += (const Vector2& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		inline Vector2& operator -= (const Vector2& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}

		inline Vector2& operator *= (float f)
		{
			x *= f;
			y *= f;

			return *this;
		}

		inline Vector2& operator /= (float f)
		{
			f = 1.0f / f;

			x *= f;
			y *= f;

			return *this;
		}

		/// <summary>
		/// ベクトルの長さ
		/// </summary>
		/// <returns></returns>
		inline float Length() const
		{
			return (float)sqrt(SquaredLength());
		}

		/// <summary>
		/// ベクトルの長さの二乗
		/// </summary>
		/// <returns></returns>
		inline float SquaredLength() const
		{
			return x * x + y * y;
		}

		/// <summary>
		/// ベクトルを正規化する
		/// </summary>
		/// <returns></returns>
		inline Vector2& Normalise()
		{
			float f = (float)sqrt(SquaredLength());

			// 0ベクトルの場合は何もしない
			if (f > 1e-06f)
			{
				f = 1.0f / f;
				x *= f;
				y *= f;
			}

			return *this;
		}

		/// <summary>
		/// 二つのベクトルの内積を計算する
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y;
		}
	};
}