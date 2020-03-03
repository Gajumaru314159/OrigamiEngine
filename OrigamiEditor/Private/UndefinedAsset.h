/**
* @file UndefinedAsset.h
*/

#pragma once

#include "Prerequisites.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief ディレクトリアセット。子要素としてEntryAssetを継承したクラスのオブジェクトを保持する。
	*/
	class UndefinedAsset :public EntryAsset
	{
	public:
		/**
		* @brief コンストラクタ。
		*/
		UndefinedAsset(String path) :EntryAsset(path) {}
	};
}