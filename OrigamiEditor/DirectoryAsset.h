/**
* @file DirectoryAsset.h
*/

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Prerequisites.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief ディレクトリアセット。子要素としてEntryAssetを継承したクラスのオブジェクトを保持する。
	*/
	class DirectoryAsset :public EntryAsset {
	public:
		DirectoryAsset(String path);


		/**
		* @brief 子要素にアセットを追加する。
		* @param asset 追加するアセット
		*/
		void AddChild(SPtr<EntryAsset>& asset);

		/**
		* @brief 子要素をリストで取得する。
		*/
		const ArrayList<SPtr<EntryAsset>>& GetChildren();
		void LoadChildEntries();

		/**
		* @brief 子要素にディレクトリを含むかどうか
		*/
		bool HasDirectory();
	private:
		// サムネ

		//! 子要素のリスト
		ArrayList<SPtr<EntryAsset>> m_Children;
	};
}