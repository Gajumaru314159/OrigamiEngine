#pragma once

#include "OrigamiAPI.h"

namespace OrigamiEngine {
	class GUID
	{
	public:
		GUID();
		GUID(String str);

		/**
		* @brief データを文字列として取り出す。"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"形式
		* @return String形式のGUID
		*/
		String ToString();

		// 比較演算子
		bool operator==(const GUID& an);
		bool operator!=(const GUID& an);

	private:
		U32 a,b,c,d;
	};
}