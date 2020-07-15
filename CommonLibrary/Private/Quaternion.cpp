#include "pch.h"
#include "Quaternion.h"
#include "Mathf.h"
#include "Matrix.h"
#include "Vector3.h"

namespace CommonLibrary
{
	Matrix Quaternion::GetMatrix()const
	{
		const F32 ww = w * w;
		const F32 xx = x * x;
		const F32 yy = y * y;
		const F32 zz = z * z;

		return Matrix(
			ww + xx - yy - zz, 2 * (x * y - w * z), 2 * (w * y + x * z), 0.0,
			2 * (x * y + w * z), ww - xx + yy - zz, 2 * (y * z - w * x), 0.0,
			2 * (x * z - w * y), 2 * (y * z + w * x), ww - xx - yy + zz, 0.0,
			0.0, 0.0, 0.0, 1.0);
	}

	Vector3 Quaternion::GetEulerAngles()const
	{
		F32 tx, ty, tz;
		F32 sx = -2 * (y * z - w * x);
		if (Mathf::Abs(sx - 1.0f) < 0.000001f)
		{
			tx = Mathf::HALF_PI;
			ty = Mathf::Atan2(2 * (x * y - w * z), w * w + x * x - y * y - z * z);
			tz = 0;
		}
		else if (Mathf::Abs(sx + 1.0f) < 0.000001f)
		{
			tx = -Mathf::HALF_PI;
			ty = Mathf::Atan2(-2 * (x * y - w * z), w * w + x * x - y * y - z * z);
			tz = 0;
		}
		else
		{
			tx = Mathf::Asin(-2 * (y * z - w * x));
			ty = Mathf::Atan2(2 * (w * y + x * z), w * w - x * x - y * y + z * z);
			tz = Mathf::Atan2(2 * (x * y + w * z), w * w - x * x + y * y - z * z);
		}


		return Vector3(Mathf::Degrees(tx), Mathf::Degrees(ty), Mathf::Degrees(tz));
	}
}