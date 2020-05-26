#include "pch.h"
#include "Affine.h"

namespace CommonLibrary
{

	const U32 Affine::COL = 4;
	const U32 Affine::ROW = 3;


	Affine::Affine()
	{
		memset(m, 0, sizeof(m));
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
	}


	Affine::Affine(
		const F32 m00, const F32 m01, const F32 m02, const F32 m03,
		const F32 m10, const F32 m11, const F32 m12, const F32 m13,
		const F32 m20, const F32 m21, const F32 m22, const F32 m23
	)
	{
		m[0][0] = m00;
		m[1][0] = m01;
		m[2][0] = m02;
		m[3][0] = m03;
		m[0][1] = m10;
		m[1][1] = m11;
		m[2][1] = m12;
		m[3][1] = m13;
		m[0][2] = m20;
		m[1][2] = m21;
		m[2][2] = m22;
		m[3][2] = m23;
	}

	void Affine::Set(
		const F32 m00, const F32 m01, const F32 m02, const F32 m03,
		const F32 m10, const F32 m11, const F32 m12, const F32 m13,
		const F32 m20, const F32 m21, const F32 m22, const F32 m23
	)
	{
		m[0][0] = m00;
		m[1][0] = m01;
		m[2][0] = m02;
		m[3][0] = m03;
		m[0][1] = m10;
		m[1][1] = m11;
		m[2][1] = m12;
		m[3][1] = m13;
		m[0][2] = m20;
		m[1][2] = m21;
		m[2][2] = m22;
		m[3][2] = m23;
	}

	void Affine::Reset()
	{
		memset(m, 0, sizeof(m));
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
		m[3][3] = 1;
	}

	void Affine::Translate(const F32 x, const F32 y, const F32 z)
	{
		m[0][3] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
		m[1][3] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
		m[2][3] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];


		//Affine mat(1, 0, 0, x,
		//		   0, 1, 0, y,
		//		   0, 0, 1, z);

		//(*this) *= mat;
	}
	void Affine::RotateX(const F32 angle)
	{
		F32 s = sin(angle);
		F32 c = cos(angle);
		Affine mat(c, -s, 0, 0,
				   s, c, 0, 0,
				   0, 0, 1, 0);

		(*this) *= mat;
	}
	void Affine::RotateY(const F32 angle)
	{

	}
	void Affine::RotateZ(const F32 angle)
	{

	}
	void Affine::Scale(const F32 x, const F32 y, const F32 z)
	{
		Affine mat(x, 0, 0, 0,
				   0, y, 0, 0,
				   0, 0, z, 0);

		(*this) *= mat;
	}




	inline bool Affine::operator == (const Affine& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (m[x][y] != v.m[x][y])return false;
		}
		return true;
	}

	inline bool Affine::operator != (const Affine& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (m[x][y] != v.m[x][y])return true;
		}
		return false;
	}

	inline Affine Affine::operator * (const Affine& o) const
	{
		F32 p1l[2][2] = { {m[0][0] + m[0][2],m[0][1] + m[0][3] },{m[1][0] + m[1][2],m[1][1] + m[1][3] } };
		F32 p1r[2][2] = { {o.m[0][0] + o.m[0][2],o.m[0][1] + o.m[0][3]} ,{o.m[1][0] + o.m[1][2],o.m[1][1] + o.m[1][3] } };
		F32 p1[2][2] = {
			{ p1l[0][0] * p1r[0][0] + p1l[0][1] * p1r[1][0] , p1l[0][0] * p1r[0][1] + p1l[0][1] * p1r[1][1] },
			{ p1l[1][0] * p1r[0][0] + p1l[1][1] * p1r[1][0] , p1l[1][0] * p1r[0][1] + p1l[1][1] * p1r[1][1] } };

		F32 p2l[2][2] = { {m[2][0] + m[2][2],m[2][1] + m[2][3] },{m[3][0] + m[3][2],m[3][1] + m[3][3] } };
		F32 p2[2][2] = {
			{ p2l[0][0] * o.m[0][0] + p2l[0][1] * o.m[1][0] , p2l[0][0] * o.m[0][1] + p2l[0][1] * o.m[1][1] },
			{ p2l[1][0] * o.m[0][0] + p2l[1][1] * o.m[1][0] , p2l[1][0] * o.m[0][1] + p2l[1][1] * o.m[1][1] } };

		F32 p3r[2][2] = { {o.m[0][2] - o.m[2][2],o.m[0][3] - o.m[2][3]} ,{o.m[1][2] - o.m[3][2],o.m[1][3] - o.m[3][3] } };
		F32 p3[2][2] = {
			{ p1l[0][0] * p1r[0][0] + p1l[0][1] * p1r[1][0] , p1l[0][0] * p1r[0][1] + p1l[0][1] * p1r[1][1] },
			{ p1l[1][0] * p1r[0][0] + p1l[1][1] * p1r[1][0] , p1l[1][0] * p1r[0][1] + p1l[1][1] * p1r[1][1] } };

		F32 p4r[2][2] = { {o.m[0][3] - o.m[0][0],o.m[0][3] - o.m[2][3]} ,{o.m[1][2] - o.m[3][2],o.m[1][3] - o.m[3][3] } };

		return Affine();
	}
}