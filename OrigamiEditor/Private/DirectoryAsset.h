/**
* @file DirectoryAsset.h
*/

#pragma once

#include "OrigamiAPI.h"

#include "EntryAsset.h"


namespace OrigamiEngine {
	/**
	* @brief ディレクトリアセット。子要素としてEntryAssetを継承したクラスのオブジェクトを保持する。
	*/
	class DirectoryAsset :public EntryAsset {
	public:
		/**
		* @brief 指定したパスをディレクトリアセットとして読み込む。
		* @param path 読み込むディレクトリのパス。
		*/
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

		/**
		* @brief このディレクトリ以下のアセットを再帰的に読み込む。
		*/
		void LoadChildEntries();

		/**
		* @brief 子要素にディレクトリを含むかどうかを調べる。
		*/
		bool HasDirectory();
	private:
		// 子要素のリスト
		ArrayList<SPtr<EntryAsset>> m_Children;
	};
}