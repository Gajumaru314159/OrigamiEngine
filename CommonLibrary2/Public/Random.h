/**
* @file Random.h
*/

#pragma once
#include "Prerequisites.h"

namespace OrigamiEngine {
	/**
	* @brief 乱数生成のためのクラス。
	*/
	class Random
	{
	public:
		/**
		* @brief 乱数のシード値を変更する。
		* @param seed シード値。
		*/
		static void SetSeed(U32 seed);

		/**
		* @brief 0から2^32までの整数の乱数を生成する。
		* @return  0から2^32までの整数の乱数。
		*/
		static U32 GetU32();

		/**
		* @brief 整数の乱数を生成する。
		* @details minimumからmaximumの間から乱数を生成する。
		* @param minimum 乱数の最小値。
		* @param maximum 乱数の最大値+1。
		* @return minimumからmaximumの間の乱数。
		*/
		static S32 Range(S32 minimum, S32 maximum);


		/**
		* @brief 小数の乱数を生成する。
		* @details minimumからmaximumの間から乱数を生成する。
		* @param minimum 乱数の最小値。
		* @param maximum 乱数の最大値。
		* @return minimumからmaximumの間の乱数。
		*/
		static F32 Range(F32 minimum, F32 maximum);
	private:
		// 乱数の生成に使用する内部値。
		static U32 x, y, z, w;
	};
}