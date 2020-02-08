#include "AssetManager.h"

#include <Windows.h>

#include "SystemManager.h"

namespace OrigamiEngine{
	void AssetManager::LoadAssets(const String path){
		if (ms_Instance->m_RootDir)ms_Instance->m_RootDir.reset();


		// Assets以下のアセットを読み込み
		ms_Instance->m_RootDir = MSPtr<DirectoryAsset>(path);
	}

	DirectoryAsset& AssetManager::GetRootDirectory() {
		assert(ms_Instance != nullptr);

		return *(ms_Instance->m_RootDir);
	}

	U32 AssetManager::AddAsset(SPtr<EntryAsset> asset)
	{
		assert(ms_Instance != nullptr);

		long id = rand();
		U32 size = (U32)(ms_Instance->m_AssetMap.size());
		ms_Instance->m_AssetMap.emplace(id,asset);

		return id;
	}

}