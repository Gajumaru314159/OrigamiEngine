#pragma once

#include "Fwd.h"

namespace CommonLibrary
{
	/**
	* @brief 3次元ベクトルのクラス。
	*/
	class DLL Vector3
	{
	public:
		//! @brief ベクトルのX値
		F32 x;
		//! @brief ベクトルのY値
		F32 y;
		//! @brief ベクトルのZ値
		F32 z;


		/**
		* @brief 3次元ベクトルの作成
		*/
		Vector3(F32 _x, F32 _y, F32 _z) :x(_x), y(_y), z(_z) {}

		/**
		* @brief 3次元ベクトルの作成
		* @details 引数なしのコンストラクタではゼロベクトルで初期化される
		*/
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

		/**
		* @brief ベクトルの長さ。
		*/
		inline float Length() const
		{
			return (float)sqrt(SquaredLength());
		}

		/**
		* @brief ベクトルの長さの二乗。
		*/
		inline float SquaredLength() const
		{
			return x * x + y * y + z * z;
		}

		/**
		* @brief ベクトルを正規化する。
		*/
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

		/**
		* @brief 二つのベクトルの内積を計算する。
		*/
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}


		/**
		* @brief 二つのベクトルの外積を計算する。
		*/
		static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		}
	};
}