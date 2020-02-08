/**
* @file AssetManager.h
*/

#pragma once

#include "OrigamiAPI.h"

#include "DirectoryAsset.h"

namespace OrigamiEngine {
	/**
	* @brief テクスチャやモデルなどのデータの読み込みと受け渡しを行う。
	* @details 必ずEnginCoreの初期化が終わってから使用すること。
	*/
	class AssetManager:public Singleton<AssetManager> {
		friend class Singleton<AssetManager>;
	public:
		/**
		* @brief 指定したディレクトリに含まれるアセットを再帰的に親ディレクトリに追加する。
		* @param path	アセットの読み込み開始地点のディレクトリのパス。
		*/
		static void LoadAssets(const String path);


		/**
		* @brief ルートディレクトリの取得。
		*/
		static DirectoryAsset& GetRootDirectory();

		/**
		* @brief アセットマネージャーで管理すべきアセットの追加
		* @param asset	追加するアセット
		* @return アセットに結びつけられたID
		*/
		static U32 AddAsset(SPtr<EntryAsset> asset);

	private:
		//! エンジンで保有しているアセット一覧
		HashMap<U32, SPtr<EntryAsset>> m_AssetMap;

		//! エクスプローラタブのAssetsフォルダに当たるエントリ
		SPtr<DirectoryAsset> m_RootDir;
	};
}