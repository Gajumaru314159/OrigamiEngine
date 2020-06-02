#include "pch.h"
#include "Affine.h"

namespace CommonLibrary
{

	const U32 Affine::COL = 3;
	const U32 Affine::ROW = 4;


	Affine::Affine()
	{
		memset(m, 0, sizeof(m));
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
	}


	Affine::Affine(
		const F32 m00, const F32 m01, const F32 m02,
		const F32 m10, const F32 m11, const F32 m12,
		const F32 m20, const F32 m21, const F32 m22,
		const F32 m30, const F32 m31, const F32 m32
	)
	{
		Set(m00, m01, m02, m10, m11, m12, m20, m21, m22, m30, m31, m32);
	}

	void Affine::Set(
		const F32 m00, const F32 m01, const F32 m02,
		const F32 m10, const F32 m11, const F32 m12,
		const F32 m20, const F32 m21, const F32 m22,
		const F32 m30, const F32 m31, const F32 m32
	)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
	}

	void Affine::Reset()
	{
		memset(m, 0, sizeof(m));
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
	}

	void Affine::Translate(const F32 x, const F32 y, const F32 z)
	{
		Affine mat(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			x, y, z
		);

		(*this) = (*this) * mat;
	}
	void Affine::RotateX(const F32 angle)
	{
		F32 s = sin(angle);
		F32 c = cos(angle);
		Affine mat(
			1, 0, 0,
			0, c, s,
			0, -s, c,
			0, 0, 0
		);

		(*this) = (*this) * mat;
	}
	void Affine::RotateY(const F32 angle)
	{
		F32 s = sin(angle);
		F32 c = cos(angle);
		Affine mat(
			c, 0, s,
			0, 1, 0,
			-s, 0, c,
			0, 0, 0
		);

		(*this) = (*this) * mat;
	}
	void Affine::RotateZ(const F32 angle)
	{
		F32 s = sin(angle);
		F32 c = cos(angle);
		Affine mat(
			c, s, 0,
			-s, c, 0,
			0, 0, 1,
			0, 0, 0
		);

		(*this) = (*this) * mat;
	}
	void Affine::Scale(const F32 x, const F32 y, const F32 z)
	{
		Affine mat(
			x, 0, 0,
			0, y, 0,
			0, 0, z,
			0, 0, 0
		);

		(*this) = (*this) * mat;
	}

	Matrix Affine::ToMatrix()const
	{
		Matrix mat;
		for (S32 y = 0; y < 4; y++)
		{
			for (S32 x = 0; x < 3; x++)
			{
				mat.m[y][x] = m[y][x];
			}
		}
		return mat;
	}




	inline bool Affine::operator == (const Affine& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (m[y][x] != v.m[y][x])return false;
		}
		return true;
	}

	inline bool Affine::operator != (const Affine& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (m[y][x] != v.m[y][x])return true;
		}
		return false;
	}

	inline Affine Affine::operator * (const Affine& o) const
	{
		Affine r;
		r.m[0][0] = 0;
		r.m[1][1] = 0;
		r.m[2][2] = 0;

		for (S32 i = 0; i < 3; i++)
		{
			for (S32 j = 0; j < 3; j++)
			{
				for (S32 k = 0; k < 3; k++)
				{
					r.m[i][j] += m[i][k] * o.m[k][j];
				}
			}
		}
		for (S32 i = 0; i < 3; i++)
		{
			r.m[3][i] = m[3][0] * o.m[0][i] + m[3][1] * o.m[1][i] + m[3][2] * o.m[2][i] + o.m[3][i];
		}

		// TODO シュトラッセンのアルゴリズムに変更
		return r;
	}
}