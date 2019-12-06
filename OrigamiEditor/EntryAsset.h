/**
* @file EntryAsset.h
*/

#pragma once
#include <filesystem>

#include "OrigamiAPI.h"

#include "UUID.h"

namespace OrigamiEngine {

	class DirectoryAsset;

	/**
	* @brief 読み込み可能なアセットの基底クラス
	*/
	class EntryAsset {
	public:
		/**
		* @brief コンストラクタ。パスを指定することで対象のアセットを読み込む。
		* @param path	アセットのパス。
		*/
		EntryAsset(String path);


		/**
		* @brief アセットのパスを取得。
		*/
		const String GetPath();

		/**
		* @brief アセット名の取得。
		*/
		const String GetName();
		/**
		* @brief アセット名の変更。
		* @param name 新しい名前。
		*/
		void SetName(String name);

	protected:
		//! アセットのパス。
		Path m_Path;
	private:
		//! アセット固有のID。
		UUID m_UUID;
	};
}