#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief 2�����x�N�g���̃N���X�B
	*/
	class Vector2
	{
	public:
		//! @brief �x�N�g����X�l
		F32 x;
		//! @brief �x�N�g����Y�l
		F32 y;


		/**
		* @brief 2�����x�N�g���̍쐬
		*/
		Vector2(F32 _x, F32 _y) :x(_x), y(_y) {}

		/**
		* @brief 2�����x�N�g���̍쐬
		* @details �����Ȃ��̃R���X�g���N�^�ł̓[���x�N�g���ŏ����������
		*/
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
			return (x < v.x && y < v.y);
		}

		inline bool operator > (const Vector2& v) const
		{
			return (x > v.x&& y > v.y);
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

		/**
		* @brief �x�N�g���̒����B
		*/
		inline float Length() const
		{
			return (float)sqrt(SquaredLength());
		}

		/**
		* @brief �x�N�g���̒����̓��B
		*/
		inline float SquaredLength() const
		{
			return x * x + y * y ;
		}

		/**
		* @brief �x�N�g���𐳋K������B
		*/
		inline Vector2& Normalise()
		{
			float f = (float)sqrt(SquaredLength());

			// 0�x�N�g���̏ꍇ�͉������Ȃ�
			if (f > 1e-06f)
			{
				f = 1.0f / f;
				x *= f;
				y *= f;
			}

			return *this;
		}

		/**
		* @brief ��̃x�N�g���̓��ς��v�Z����B
		*/
		static float Dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y ;
		}
	};
}