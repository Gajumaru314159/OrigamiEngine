#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class UUID
	{
	public:
		UUID();
		UUID(String str);

		/**
		* @brief データを文字列として取り出す。"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"形式
		* @return String形式のUUID
		*/
		String ToString();

		// 比較演算子
		bool operator==(const UUID& an);
		bool operator!=(const UUID& an);

	private:
		U32 a,b,c,d;
	};
}