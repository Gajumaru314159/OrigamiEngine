#pragma once

#include "Fwd.h"
#include "Matrix.h"

namespace CommonLibrary
{
	/// <summary>
	/// 3次元ベクトルのクラス
	/// </summary>
	class DLL Vector3
	{
	public:
		/// <summary>ベクトルのx成分 </summary>
		F32 x;
		/// <summary>ベクトルのy成分 </summary>
		F32 y;
		/// <summary>ベクトルのz成分 </summary>
		F32 z;


		/// <summary>
		/// 与えられたx,y,z成分から新しいベクトルを生成する
		/// </summary>
		/// <param name="_x">x成分</param>
		/// <param name="_y">y成分</param>
		/// <param name="_z">z成分</param>
		Vector3(F32 _x, F32 _y, F32 _z) :x(_x), y(_y), z(_z) {}
		Vector3() :Vector3(0, 0, 0) {}


		inline Vector3& operator = (const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		inline bool operator == (const Vector3& v) const
		{
			return (x == v.x && y == v.y && z == v.z);
		}

		inline bool operator != (const Vector3& v) const
		{
			return (x != v.x || y != v.y || z != v.z);
		}

		inline bool operator < (const Vector3& v) const
		{
			return (x < v.x&& y < v.y&& z < v.z);
		}

		inline bool operator > (const Vector3& v) const
		{
			return (x > v.x && y > v.y && z > v.z);
		}

		inline Vector3 operator + (const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		inline Vector3 operator - (const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		inline Vector3 operator * (float f) const
		{
			return Vector3(x * f, y * f, z * f);
		}

		inline Vector3 operator * (const Vector3& v) const
		{
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		inline Vector3 operator / (float f) const
		{
			f = 1.0f / f;
			return Vector3(x * f, y * f, z * f);
		}

		inline Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		inline friend Vector3 operator * (float f, const Vector3& v)
		{
			return Vector3(f * v.x, f * v.y, f * v.z);
		}

		inline Vector3& operator += (const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		inline Vector3& operator -= (const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		inline Vector3& operator *= (float f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		inline Vector3& operator /= (float f)
		{
			f = 1.0f / f;

			x *= f;
			y *= f;
			z *= f;

			return *this;
		}



		Vector3 operator* (const Matrix& mat)const;

		Vector3 operator*= (const Matrix& mat);


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
		inline Vector3& Normalise()
		{
			float f = (float)sqrt(SquaredLength());

			// 0ベクトルの場合は何もしない
			if (f > 1e-06f)
			{
				f = 1.0f / f;
				x *= f;
				y *= f;
				z *= f;
			}

			return *this;
		}

		/// <summary>
		/// 二つのベクトルの内積を計算する
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}


		/// <summary>
		/// 二つのベクトルの外積を計算する
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		}
	};
}