#pragma once

#include <string>

namespace CommonLibrary
{
	/// <summary>
	/// テキストエンコーディング変換マクロ
	/// </summary>
	#define TC(str) u8##str

	using Char = char;

	class String :public std::string
	{
	private:
		using base_type = std::string;

	public:
		String() :base_type() {}

		/// <summary>
		/// char配列からStringオブジェクトを生成する
		/// </summary>
		/// <param name="str">char配列のポインタ</param>
		String(const char* str) : base_type(str) {}

		/// <summary>
		///  std::stringオブジェクトから新しいStringオブジェクトを生成する
		/// </summary>
		/// <param name="str">元となるstd::stringオブジェクト</param>
		String(const std::string& str) : base_type(str) {}

		/// <summary>
		/// Stringオブジェクトから新しいStringオブジェクトを生成する
		/// </summary>
		/// <param name="str">元となるStringオブジェクト</param>
		String(const String& str) : base_type(str) {}

		String& operator=(const char* str)
		{
			base_type::operator=(str);
			return *this;
		}
	};
}

namespace std
{
	template<> struct hash<CommonLibrary::String>
	{
		std::size_t operator()(CommonLibrary::String const& s) const noexcept
		{
			return std::hash<std::string>{}(s);
		}
	};
}