#pragma once

#include "Fwd.h"


namespace CommonLibrary
{
	/// <summary>
	/// 乱数生成のためのクラス
	/// </summary>
	class DLL Random
	{
	public:
		/// <summary>
		/// 乱数のシード値を変更する
		/// </summary>
		/// <param name="seed">シード値</param>
		static void SetSeed(U32 seed);

		/// <summary>
		/// 0から2^32までの整数の乱数を生成する
		/// </summary>
		/// <returns>生成された乱数</returns>
		static U32 GetU32();

		/// <summary>
		/// 整数の乱数を生成する
		/// </summary>
		/// <remarks>
		/// minimumからmaximumの間から乱数を生成する
		/// </remarks>
		/// <param name="minimum">乱数の最小値</param>
		/// <param name="maximum">乱数の最大値</param>
		/// <returns>minimum以上maximum以下の乱数</returns>
		static S32 Range(S32 minimum, S32 maximum);

		/// <summary>
		/// 小数の乱数を生成する
		/// </summary>
		/// <remarks>
		/// minimumからmaximumの間から乱数を生成する
		/// </remarks>
		/// <param name="minimum">乱数の最小値</param>
		/// <param name="maximum">乱数の最大値</param>
		/// <returns>minimum以上maximum以下の乱数</returns>
		static F32 Range(F32 minimum, F32 maximum);
	};
}