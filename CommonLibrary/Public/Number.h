#pragma once

namespace CommonLibrary
{
	/// <summary>
	/// 指定した型の最大の数値
	/// </summary>
	template <class Type>
	constexpr Type Largest = std::numeric_limits<Type>::max();

	/// <summary>
	/// 指定した型の最小の数値
	/// </summary>
	template <class Type>
	constexpr Type Smallest = std::numeric_limits<Type>::lowest();
}