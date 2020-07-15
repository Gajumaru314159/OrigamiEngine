#pragma once

#include "Fwd.h"

namespace CommonLibrary
{
	class Matrix;
	class Vector3;

	class DLL Quaternion
	{
	public:
		F32 x, y, z, w;
	public:
		Quaternion(F32 _x, F32 _y, F32 _z, F32 _w) :x(_x), y(_y), z(_z), w(_w) {};
		Quaternion() :Quaternion(0, 0, 0, 0) {};
		Quaternion(F32 roll, F32 pitch, F32 yaw)
		{
			F32 cx = cos(roll * 0.5f);
			F32 cy = cos(pitch * 0.5f);
			F32 cz = cos(yaw * 0.5f);
			F32 sx = sin(roll * 0.5f);
			F32 sy = sin(pitch * 0.5f);
			F32 sz = sin(yaw * 0.5f);
			*this = Quaternion(sx, 0, 0, cx) * Quaternion(0, sy, 0, cy) * Quaternion(0, 0, sz, cz);
		}

		/// <summary>
		/// 逆回転を表すQuaternionを取得
		/// </summary>
		/// <returns></returns>
		Quaternion GetInverse() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		/// <summary>
		/// 行列表現を取得
		/// </summary>
		/// <returns></returns>
		Matrix GetMatrix()const;

		/// <summary>
		/// オイラー角での表現を取得
		/// </summary>
		/// <returns></returns>
		Vector3 GetEulerAngles()const;


		inline Quaternion operator * (const Quaternion& quat) const
		{
			return Quaternion(y * quat.z - z * quat.y + x * quat.w + w * quat.x,
				z * quat.x - x * quat.z + y * quat.w + w * quat.y,
				x * quat.y - y * quat.x + z * quat.w + w * quat.z,
				w * quat.w - x * quat.x - y * quat.y - z * quat.z);
		}

		inline Quaternion operator *= (const Quaternion& quat)
		{
			F32 x = this->x;
			F32 y = this->y;
			F32 z = this->z;
			F32 w = this->w;

			this->x = y * quat.z - z * quat.y + x * quat.w + w * quat.x;
			this->y = z * quat.x - x * quat.z + y * quat.w + w * quat.y;
			this->z = x * quat.y - y * quat.x + z * quat.w + w * quat.z;
			this->w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
			return *this;
		}

		inline Quaternion operator / (const Quaternion& quat) const
		{
			return (*this) * quat.GetInverse();
		}

		inline Quaternion operator /= (const Quaternion& quat)
		{
			(*this) *= quat.GetInverse();
			return *this;
		}
	};
}