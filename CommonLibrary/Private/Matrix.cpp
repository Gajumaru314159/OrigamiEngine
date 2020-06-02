#include "pch.h"
#include "Matrix.h"
#include "Mathf.h"

namespace CommonLibrary
{
	const S32 Matrix::COL = 4;
	const S32 Matrix::ROW = 4;

	Matrix::Matrix()
	{
		Reset();
	}


	Matrix::Matrix(const F32 m00, const F32 m01, const F32 m02, const F32 m03,
				   const F32 m10, const F32 m11, const F32 m12, const F32 m13,
				   const F32 m20, const F32 m21, const F32 m22, const F32 m23,
				   const F32 m30, const F32 m31, const F32 m32, const F32 m33)
	{
		Set(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33);
	}


	Vector4 Matrix::GetColumn(const S32 index)
	{
		if (index < 0 || COL <= index)return Vector4();
		return Vector4(m[index][0], m[index][1], m[index][2], m[index][3]);
	}
	Vector4 Matrix::GetRow(const S32 index)
	{
		if (index < 0 || ROW <= index)return Vector4();
		return Vector4(m[0][index], m[1][index], m[2][index], m[3][index]);
	}

	void Matrix::SetColumn(const S32 index, const Vector4& column)
	{
		if (index < 0 || COL <= index)return;
		m[index][0] = column.x;
		m[index][1] = column.y;
		m[index][2] = column.z;
		m[index][3] = column.w;
	}
	void Matrix::SetRow(const S32 index, const Vector4& column)
	{
		if (index < 0 || ROW <= index)return;
		m[0][index] = column.x;
		m[1][index] = column.y;
		m[2][index] = column.z;
		m[3][index] = column.w;
	}

	void Matrix::Set(const F32 m00, const F32 m01, const F32 m02, const F32 m03,
					 const F32 m10, const F32 m11, const F32 m12, const F32 m13,
					 const F32 m20, const F32 m21, const F32 m22, const F32 m23,
					 const F32 m30, const F32 m31, const F32 m32, const F32 m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	void Matrix::Translate(const Vector3& position)
	{
		Matrix mat(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			position.x, position.y, position.z, 1);
		(*this) *= mat;
	}
	void Matrix::Translate(const F32 x, const F32 y, const F32 z)
	{
		Matrix mat(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1);
		(*this) *= mat;
	}
	void Matrix::Rotate(const Vector3& rotation)
	{
		const F32 sx = Mathf::Sin(rotation.x);
		const F32 cx = Mathf::Cos(rotation.x);
		const F32 sy = Mathf::Sin(rotation.y);
		const F32 cy = Mathf::Cos(rotation.y);
		const F32 sz = Mathf::Sin(rotation.z);
		const F32 cz = Mathf::Cos(rotation.z);


	}
	void Matrix::Rotate(const Quaternion& pos)
	{

	}
	void Matrix::Rotate(const F32 x, const F32 y, const F32 z)
	{
		const F32 sx = Mathf::Sin(x);
		const F32 cx = Mathf::Cos(x);
		const F32 sy = Mathf::Sin(y);
		const F32 cy = Mathf::Cos(y);
		const F32 sz = Mathf::Sin(z);
		const F32 cz = Mathf::Cos(z);
	}
	void Matrix::Scale(const Vector3& scale)
	{
		Matrix mat(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1);
		(*this) *= mat;
	}
	void Matrix::Scale(const F32 x, const F32 y, const F32 z)
	{
		Matrix mat(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
		(*this) *= mat;
	}

	void Matrix::Reset()
	{
		memset(m, 0, sizeof(m));
		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
		m[3][3] = 1;
	}


	F32 Matrix::Determinant()
	{
		F32 ret = 0;
		for (S32 i = 0; i < ROW; i++)
		{
			F32 tmp = 1;
			F32 tmp2 = 1;
			for (S32 j = 0; j < COL; j++)
			{
				tmp *= m[(i + j) % COL][j];
				tmp2 *= m[(i + j) % COL][COL - j - 1];
			}
			ret += tmp - tmp2;
		}
		return ret;
	}

	Matrix Matrix::Inverted()
	{
		Matrix ret;
		return ret;
	}

	Matrix Matrix::Transpose()
	{
		Matrix ret;
		for (S32 i = 0; i < COL; i++)
		{
			for (S32 j = 0; j < ROW; j++)
			{
				ret.m[i][j] = m[j][i];
			}
		}
		return ret;
	}


	Matrix Matrix::Frustum(const F32 left, const F32 right, const F32 bottom, const F32 top, const F32 zNear, const F32 zFar)
	{
		Matrix ret;
		return ret;
	}

	Matrix Matrix::Frustum(FrustumDesc desc)
	{
		Matrix ret;
		return ret;
	}

	Matrix Matrix::Perspective(const F32 fov, const F32 aspect, const F32 zNear, const F32 zFar)
	{
		Matrix ret;
		return ret;
	}

	Matrix Matrix::Ortho(const F32 left, const F32 right, const F32 bottom, const F32 top, const F32 zNear, const F32 zFar)
	{
		Matrix ret;
		return ret;
	}


	bool Matrix::operator == (const Matrix& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (Mathf::Approximately(m[y][x], v.m[y][x]) == false)return false;
		}
		return true;
	}

	bool Matrix::operator != (const Matrix& v) const
	{
		for (U32 y = 0; y < ROW; y++)for (U32 x = 0; x < COL; x++)
		{
			if (Mathf::Approximately(m[y][x], v.m[y][x]) == false)return true;
		}
		return false;
	}

	Matrix Matrix::operator * (const Matrix& other) const
	{
		Matrix result;
		result.m[0][0] = 0;
		result.m[1][1] = 0;
		result.m[2][2] = 0;
		result.m[3][3] = 0;

		for (S32 i = 0; i < COL; i++)
		{
			for (S32 j = 0; j < ROW; j++)
			{
				for (S32 k = 0; k < ROW; k++)
				{
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}

		return result;
	}

	Matrix Matrix::operator *= (const Matrix& other)
	{
		Matrix result;
		result.m[0][0] = 0;
		result.m[1][1] = 0;
		result.m[2][2] = 0;
		result.m[3][3] = 0;

		for (S32 i = 0; i < COL; i++)
		{
			for (S32 j = 0; j < ROW; j++)
			{
				for (S32 k = 0; k < ROW; k++)
				{
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}

		(*this) = result;
		return result;
	}
}