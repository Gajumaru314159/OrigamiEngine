#pragma once

#include "Prerequisites.h"

namespace OrigamiEngine {
	class Path{
	public:
		Path(String path);

		void Set(String path);
		String FileName();
		String Extension();
		bool HasExtention();
		String Fullpath();
		String Directory();
	private:
		String m_Path;
		bool m_HasExtention;
	};
}