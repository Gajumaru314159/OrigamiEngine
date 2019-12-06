/**
* @file Vector4.h
*/

#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class Vector4
	{
	public:
		//! 各ベクトルの値
		F32 x, y, z, w;


		/**
		* @brief 四次元ベクトルの作成
		* @param x
		* @param y
		* @param z
		* @param w
		*/
		Vector4(F32 _x, F32 _y, F32 _z, F32 _w):x(_x),y(_y),z(_z),w(_w){}

		/**
		* @brief 引数なしのコンストラクタではゼロベクトルで初期化される
		*/
		Vector4() :Vector4(0, 0, 0, 0) {}


		inline Vector4& operator = (const Vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		inline bool operator == (const Vector4& v) const
		{
			return (x == v.x && y == v.y && z == v.z);
		}

		inline bool operator != (const Vector4 & v) const
		{
			return (x != v.x || y != v.y || z != v.z);
		}

		inline Vector4 operator + (const Vector4 & v) const
		{
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		inline Vector4 operator - (const Vector4 & v) const
		{
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		inline Vector4 operator * (float f) const
		{
			return Vector4(x * f, y * f, z * f, w * f);
		}

		inline Vector4 operator * (const Vector4 & v) const
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

		inline friend Vector4 operator * (float f, const Vector4 & v)
		{
			return Vector4(f * v.x, f * v.y, f * v.z, f * v.w);
		}

		inline Vector4& operator += (const Vector4 & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		inline Vector4& operator -= (const Vector4 & v)
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



		/**
		* @brief ベクトルの長さを取得
		* @return ベクトルの長さ
		*/
		inline float Length() const
		{
			return (float)sqrt(SquaredLength());
		}

		/**
		* @brief ベクトルの長さの二乗値を取得
		* @return ベクトルの長さの二乗値
		*/
		inline float SquaredLength() const
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		* @brief ベクトルを正規化する
		*/
		inline Vector4& Normalise()
		{
			float f = (float)sqrt(SquaredLength());

			// Will also work for zero-sized vectors, but will change nothing
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
		* @brief ベクトルの内積を取得
		* @return ベクトルの内積
		*/
		inline float Dot(const Vector4 & v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}


		inline Vector4 Cross(const Vector4 & v) const
		{
			return Vector4(y * v.z - z * v.y, z * v.w - w * v.z, w * v.x - x * v.w, x * v.y - y * v.x);
		}

		inline bool operator < (const Vector4 & v) const
		{
			return (x < v.x && y < v.y && z < v.z && w <v.w);
		}

		inline bool operator > (const Vector4 & v) const
		{
			return (x > v.x && y > v.y && z > v.z && w>v.w);
		}
	};
}