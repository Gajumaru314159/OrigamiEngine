#include "DirectoryAsset.h"

#include <Windows.h>

#include "UndefinedAsset.h"
#include "AssetManager.h"

namespace OrigamiEngine {

	DirectoryAsset::DirectoryAsset(String path) :EntryAsset(path) {
		LoadChildEntries();
	}



	void DirectoryAsset::AddChild(SPtr<EntryAsset>& child) {
		m_Children.emplace_back(child);
	}
	
	const ArrayList<SPtr<EntryAsset>>& DirectoryAsset::GetChildren()
	{
		return m_Children;
	}

	void DirectoryAsset::LoadChildEntries()
	{
		HANDLE hFind;				// �n���h��
		WIN32_FIND_DATA win32fd;	// �t�@�C�����

		String searchPath = m_Path.Fullpath() + L"\\*";

		// �n���h�����擾���t�@�C������ۑ�����
		hFind = FindFirstFile(searchPath.c_str(), &win32fd);

		// ����������Ȃ������Ƃ�
		if (hFind == INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);
			return;
		}
		do
		{
			String childPath = m_Path.Fullpath() + L"\\" + win32fd.cFileName;
			if ((wcscmp(win32fd.cFileName, L".") == 0) || (wcscmp(win32fd.cFileName, L"..") == 0))continue;
			
			SPtr<EntryAsset> childPtr;

			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// �t�H���_�̂Ƃ�
				childPtr = MSPtr<DirectoryAsset>(childPath);
			}
			else if((wcscmp(win32fd.cFileName, L".") != 0) && (wcscmp(win32fd.cFileName, L"..") != 0))
			{
				// �t�@�C���̂Ƃ�
				String extention = m_Path.Extension();


				if (extention==L"png")
				{

				}
				else
				{
					childPtr = MSPtr<UndefinedAsset>(childPath);
				}
			}

			// �L���ȃA�Z�b�g�̎��̂ݏ���
			if (childPtr)
			{
				m_Children.emplace_back(childPtr);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}


	bool DirectoryAsset::HasDirectory()
	{
		for (auto& child : m_Children)
		{
			if (typeid(*child) == typeid(DirectoryAsset))
			{
				return true;
			}
		}
		return false;
	}
}