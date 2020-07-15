#pragma once
#include "Fwd.h"

namespace CommonLibrary
{
	class Vector3;
	class Vector4;
	class Quaternion;

	struct FrustumDesc
	{
		F32 left;
		F32 right;
		F32 bottom;
		F32 top;
		F32 zNear;
		F32 zFar;
	};

	class DLL Matrix
	{
	private:
		static const S32 COL;
		static const S32 ROW;
	public:
		F32 m[4][4];


		Matrix();

		Matrix(const F32 m00, const F32 m01, const F32 m02, const F32 m03,
			const F32 m10, const F32 m11, const F32 m12, const F32 m13,
			const F32 m20, const F32 m21, const F32 m22, const F32 m23,
			const F32 m30, const F32 m31, const F32 m32, const F32 m33);


		Vector4 GetColumn(const S32 index)const;
		Vector4 GetRow(const S32 index)const;

		void SetColumn(const S32 index, const Vector4& column);
		void SetRow(const S32 index, const Vector4& column);

		void Set(const F32 m00, const F32 m01, const F32 m02, const F32 m03,
			const F32 m10, const F32 m11, const F32 m12, const F32 m13,
			const F32 m20, const F32 m21, const F32 m22, const F32 m23,
			const F32 m30, const F32 m31, const F32 m32, const F32 m33);

		void Translate(const F32 x, const F32 y, const F32 z);
		void Translate(const Vector3& posisiton);
		void Rotate(const F32 x, const F32 y, const F32 z);
		void Rotate(const Vector3& rotation);
		void Rotate(const Quaternion& rotation);
		void Scale(const F32 x, const F32 y, const F32 z);
		void Scale(const Vector3& scale);

		void Reset();


		F32 Determinant();
		Matrix Inverted();
		Matrix Transpose();


		static Matrix Frustum(const F32 left, const F32 right, const F32 bottom, const F32 top, const F32 zNear, const F32 zFar);
		static Matrix Frustum(FrustumDesc desc);

		static Matrix Perspective(const F32 fov, const F32 aspect, const F32 zNear, const F32 zFar);

		static Matrix Ortho(const F32 left, const F32 right, const F32 bottom, const F32 top, const F32 zNear, const F32 zFar);



		inline Matrix& operator = (const Matrix& other)
		{
			memcpy_s(m, sizeof(m), other.m, sizeof(m));

			return *this;
		}

		bool operator == (const Matrix& v) const;

		bool operator != (const Matrix& v) const;

		Matrix operator * (const Matrix& other) const;
		Matrix operator *= (const Matrix& o);
	};

}