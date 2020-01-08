#pragma once

#include "Container.h"

#include <vector>
#include <memory>

#include "ITab.h"



namespace OrigamiEngine {
	class TabContainer :public Container
	{
	public:
		~TabContainer();

		void Draw(const F32 x, const F32 y, const F32 width, const F32 height)override;
		bool AddTab(ITab* tab, const U32 index = -1)override;
	private:
		std::vector<std::unique_ptr<ITab>> m_Tabs;
		int m_ActiveIndex;
	};

}