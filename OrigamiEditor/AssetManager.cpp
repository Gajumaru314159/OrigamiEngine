#include "AssetManager.h"

#include <Windows.h>

#include "SystemManager.h"

namespace OrigamiEngine{


	AssetManager::AssetManager()
	{
	}

	// 指定フォルダ以下のファイルとフォルダの読み込み
	void AssetManager::LoadAssets(const String path){
		if (m_RootDir)m_RootDir.reset();


		// Assets以下のアセットを読み込み
		m_RootDir = MSPtr<DirectoryAsset>(path);
	}

	DirectoryAsset& AssetManager::GetRootDirectory() {
		return *GetInstance().m_RootDir;
	}


	U32 AssetManager::AddAsset(SPtr<EntryAsset> asset)
	{
		long id = rand();
		U32 size = GetInstance().m_AssetMap.size();
		GetInstance().m_AssetMap.emplace(id,asset);

		return id;
	}

}