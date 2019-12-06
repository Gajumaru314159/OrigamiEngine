#include "AssetManager.h"

#include <Windows.h>

#include "SystemManager.h"

namespace OrigamiEngine{


	AssetManager::AssetManager()
	{
	}

	// �w��t�H���_�ȉ��̃t�@�C���ƃt�H���_�̓ǂݍ���
	void AssetManager::LoadAssets(const String path){
		if (m_RootDir)m_RootDir.reset();


		// Assets�ȉ��̃A�Z�b�g��ǂݍ���
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