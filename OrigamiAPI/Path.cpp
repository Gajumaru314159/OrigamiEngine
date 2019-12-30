#include "pch.h"
#include "Path.h"



namespace OrigamiEngine {
	Path::Path(String path){
		Set(path);
	}

	void Path::Set(String path) {
		m_Path = path;

		std::size_t pos;
		auto len = 2;
		while (pos = m_Path.find(L"\\") != std::string::npos) {
			m_Path.replace(pos, len, L"/");
		}
		m_HasExtention = (Extension() != L"");
	}

	String Path::Fullpath() {
		return m_Path;
	}

	String Path::FileName() {
		auto pos = m_Path.rfind(L"/");
		if (pos == std::string::npos) {
			return m_Path;
		}
		return m_Path.substr(pos);
	}

	String Path::Extension() {
		String fileName = FileName();
		auto pos = fileName.rfind(L".");
		if (pos == std::string::npos) {
			return L"";
		}
		return fileName.substr(pos);
	}

	String Path::Directory() {
		auto pos = m_Path.rfind(L"/");
		if (pos == std::string::npos) {
			return L"";
		}
		return m_Path.substr(0,pos);
	}

	bool Path::HasExtention() {
		return m_HasExtention;
	}
}