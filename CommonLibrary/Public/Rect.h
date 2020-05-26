#pragma once

#include "Fwd.h"
#include "Vector2.h"

namespace CommonLibrary
{
	/// <summary>
	/// 矩形領域を表現するクラス
	/// </summary>
	class DLL Rect
	{
	public:
		/// <summary>
		/// 原点から始まる大きさ(100,100)の矩形領域を生成する
		/// </summary>
		Rect();
		/// <summary>
		/// 新しい矩形領域を生成する
		/// </summary>
		/// <param name="_x">矩形の始まるx座標</param>
		/// <param name="_y">矩形の始まるy座標</param>
		/// <param name="_width">矩形の横幅</param>
		/// <param name="_height">矩形の高さ</param>
		Rect(F32 _x, F32 _y, F32 _width, F32 _height);
		/// <summary>
		/// 新しい矩形領域を作成する
		/// </summary>
		/// <param name="_position">矩形の始まる座標</param>
		/// <param name="_size">矩形の大きさ</param>
		Rect(const Vector2& _position, const Vector2& _size);

		//! 矩形の左上座標。
		Vector2 position;

		//! 矩形のサイズ
		Vector2 size;
	};
}