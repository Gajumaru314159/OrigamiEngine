#pragma once
#include"Fwd.h"

#include "Vector3.h"

namespace CommonLibrary
{
	/// <summary>
	/// 3x4アフィン行列クラス
	/// </summary>
	/// <remarks>
	/// 行優先行列 [y][x]
	/// </remarks>
	class DLL Affine
	{
	private:
		static const U32 COL;
		static const U32 ROW;
	public:
		F32 m[3][4];


		/// <summary>
		/// 単位行列を生成する
		/// </summary>
		Affine();

		Affine(
			const F32 m00, const F32 m01, const F32 m02, const F32 m03,
			const F32 m10, const F32 m11, const F32 m12, const F32 m13,
			const F32 m20, const F32 m21, const F32 m22, const F32 m23
		);

		/// <summary>
		/// 行列の設定をまとめて行う
		/// </summary>
		/// <param name="m00"></param>
		/// <param name="m01"></param>
		/// <param name="m02"></param>
		/// <param name="m03"></param>
		/// <param name="m10"></param>
		/// <param name="m11"></param>
		/// <param name="m12"></param>
		/// <param name="m13"></param>
		/// <param name="m20"></param>
		/// <param name="m21"></param>
		/// <param name="m22"></param>
		/// <param name="m23"></param>
		void Set(
			const F32 m00, const F32 m01, const F32 m02, const F32 m03,
			const F32 m10, const F32 m11, const F32 m12, const F32 m13,
			const F32 m20, const F32 m21, const F32 m22, const F32 m23
		);

		/// <summary>
		/// 行列を単位行列にする
		/// </summary>
		void Reset();

		void Translate(const F32 x, const F32 y, const F32 z);
		void RotateX(const F32 angle);
		void RotateY(const F32 angle);
		void RotateZ(const F32 angle);
		void Scale(const F32 x, const F32 y, const F32 z);


		inline Affine& operator = (const Affine& v)
		{
			memcpy_s(m, sizeof(m), v.m, sizeof(m));

			return *this;
		}

		inline bool operator == (const Affine& v) const;

		inline bool operator != (const Affine& v) const;

		inline Affine operator * (const Affine& o) const;
		inline Affine operator *= (const Affine& o) const;
	};
}