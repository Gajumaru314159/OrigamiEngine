#pragma once

#include "Fwd.h"
#include "Matrix.h"

namespace CommonLibrary
{

	/// <summary>
	/// 3次元ベクトルのクラス
	/// </summary>
	class DLL Vector4
	{
	public:
		/// <summary>ベクトルのx成分 </summary>
		F32 x;
		/// <summary>ベクトルのy成分 </summary>
		F32 y;
		/// <summary>ベクトルのz成分 </summary>
		F32 z;
		/// <summary>ベクトルのw成分 </summary>
		F32 w;




		/// <summary>
		/// 与えられたx,y,z,w成分から新しいベクトルを生成する
		/// </summary>
		/// <param name="_x">x成分</param>
		/// <param name="_y">y成分</param>
		/// <param name="_z">z成分</param>
		/// <param name="_w">z成分</param>
		Vector4(const F32 _x, const F32 _y, const F32 _z, const F32 _w) :x(_x), y(_y), z(_z), w(_w)
		{}


		Vector4() :Vector4(0, 0, 0, 0)
		{

		}


		inline Vector4& operator = (const Vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;

			return *this;
		}

		inline bool operator == (const Vector4& v) const
		{
			return (x == v.x && y == v.y && z == v.z && w == v.w);
		}

		inline bool operator != (const Vector4& v) const
		{
			return (x != v.x || y != v.y || z != v.z || w != v.w);
		}

		inline bool operator < (const Vector4& v) const
		{
			return (x < v.x&& y < v.y&& z < v.z&& w < v.w);
		}

		inline bool operator > (const Vector4& v) const
		{
			return (x > v.x && y > v.y && z > v.z && w > v.w);
		}

		inline Vector4 operator + (const Vector4& v) const
		{
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		inline Vector4 operator - (const Vector4& v) const
		{
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		inline Vector4 operator * (float f) const
		{
			return Vector4(x * f, y * f, z * f, w * f);
		}

		inline Vector4 operator * (const Vector4& v) const
		{
			return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		inline Vector4 operator / (float f) const
		{
			f = 1.0f / f;
			return Vector4(x * f, y * f, z * f, w * f);
		}

		inline Vector4 operator - () const
		{
			return Vector4(-x, -y, -z, -w);
		}

		inline friend Vector4 operator * (float f, const Vector4& v)
		{
			return Vector4(f * v.x, f * v.y, f * v.z, f * v.w);
		}

		inline Vector4& operator += (const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		inline Vector4& operator -= (const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}

		inline Vector4& operator *= (float f)
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;

			return *this;
		}

		inline Vector4& operator /= (float f)
		{
			f = 1.0f / f;

			x *= f;
			y *= f;
			z *= f;
			w *= f;

			return *this;
		}




		Vector4 operator* (const Matrix& mat)const;

		Vector4 operator*= (const Matrix& mat);


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
			return x * x + y * y + z * z;
		}

		/// <summary>
		/// ベクトルを正規化する
		/// </summary>
		/// <returns></returns>
		inline Vector4& Normalise()
		{
			float f = (float)sqrt(SquaredLength());

			// 0ベクトルの場合は何もしない
			if (f > 1e-06f)
			{
				f = 1.0f / f;
				x *= f;
				y *= f;
				z *= f;
				w *= f;
			}

			return *this;
		}

		/// <summary>
		/// 二つのベクトルの内積を計算する
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Dot(const Vector4& a, const Vector4& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}


		/// <summary>
		/// 二つのベクトルの外積を計算する
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static Vector4 Cross(const Vector4& a, const Vector4& b)
		{
			return Vector4(a.y * b.z - a.z * b.y, a.z * b.w - a.w * b.z, a.w * b.x - a.x * b.w, a.x * b.y - a.y * b.x);
		}
	};
}