#pragma once

#include "Fwd.h"


namespace CommonLibrary
{
	/// <summary>
	/// 2�����x�N�g���̃N���X
	/// </summary>
	class DLL Vector2
	{
	public:
		/// <summary>�x�N�g����x���� </summary>
		F32 x;
		/// <summary>�x�N�g����y���� </summary>
		F32 y;


		/// <summary>
		/// �^����ꂽx,y��������V�����x�N�g���𐶐�����
		/// </summary>
		/// <param name="_x">x����</param>
		/// <param name="_y">y����</param>
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
		/// �x�N�g���̒���
		/// </summary>
		/// <returns></returns>
		inline float Length() const
		{
			return (float)sqrt(SquaredLength());
		}

		/// <summary>
		/// �x�N�g���̒����̓��
		/// </summary>
		/// <returns></returns>
		inline float SquaredLength() const
		{
			return x * x + y * y;
		}

		/// <summary>
		/// �x�N�g���𐳋K������
		/// </summary>
		/// <returns></returns>
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

		/// <summary>
		/// ��̃x�N�g���̓��ς��v�Z����
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