#include "pch.h"
#include "Path.h"

namespace CommonLibrary
{
	Path::Path(const String& path)
	{
		Set(path);
	}

	S32 Path::Set(const String& path)
	{
		m_Path = path;

		std::size_t pos;
		auto len = 2;
		while (pos = m_Path.find(TC("\\")) != std::string::npos)
		{
			m_Path.replace(pos, len, TC("/"));
		}
		m_HasExtention = (0 < Extension().size());

		// TODO •s³‚ÈƒpƒX‚Å‚ ‚ê‚Îm_Path‚ð‹ó•¶Žš‚É‚·‚é
		return 0;
	}

	String Path::Fullpath()const
	{
		return m_Path;
	}

	String Path::FileName()const
	{
		auto pos = m_Path.rfind(TC("/"));
		if (pos == std::string::npos)
		{
			return m_Path;
		}
		return m_Path.substr(pos);
	}

	String Path::Extension()const
	{
		String fileName = FileName();
		auto pos = fileName.rfind(TC("."));
		if (pos == std::string::npos)
		{
			return TC("");
		}
		return fileName.substr(pos + 1);
	}

	String Path::Directory()const
	{
		auto pos = m_Path.rfind(TC("/"));
		if (pos == std::string::npos)
		{
			return TC("");
		}
		return m_Path.substr(0, pos);
	}

	bool Path::HasExtention()const
	{
		return m_HasExtention;
	}
}