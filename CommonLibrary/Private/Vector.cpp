#include "pch.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

namespace CommonLibrary
{
	inline Vector3 Vector3::operator* (const Matrix& mat)const
	{
		return Vector3(
			x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + mat.m[3][0],
			x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + mat.m[3][1],
			x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + mat.m[3][2]);
	}

	inline Vector3 Vector3::operator*= (const Matrix& mat)
	{
		float nx = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + mat.m[3][0];
		float ny = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + mat.m[3][1];
		float nz = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + mat.m[3][2];
		x = nx;
		y = ny;
		z = nx;
		return *this;
	}



	Vector4 Vector4::operator* (const Matrix& mat)const
	{
		return Vector4(
			x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + mat.m[3][0],
			x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + mat.m[3][1],
			x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + mat.m[3][2],
			x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + mat.m[3][3]);
	}

	Vector4 Vector4::operator*= (const Matrix& mat)
	{
		float nx = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + mat.m[3][0];
		float ny = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + mat.m[3][1];
		float nz = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + mat.m[3][2];
		float nw = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + mat.m[3][3];
		x = nx;
		y = ny;
		z = nx;
		w = nw;
		return *this;
	}
}