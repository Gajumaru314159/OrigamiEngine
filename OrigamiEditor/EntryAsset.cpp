#include "EntryAsset.h"

namespace OrigamiEngine {
	EntryAsset::EntryAsset(String path) :
		m_Path(path)//,
		//m_GUID()
	{
		// メタファイルの生成

		// GUIDの生成
		//String s = m_GUID.ToString();
	}

	const String EntryAsset::GetPath()
	{
		return m_Path.Fullpath();
	}

	const String EntryAsset::GetName()
	{
		return m_Path.FileName();
	}

	void EntryAsset::SetName(String name)
	{
		m_Path.Set(m_Path.Directory()+L"/"+name);
	}
}