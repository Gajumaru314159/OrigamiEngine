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

		void Draw(const int x, const int y, const int width, const int height)override;
		void AddTab(std::unique_ptr<ITab>&& tab, const unsigned int index = -1);
	private:
		std::vector<std::unique_ptr<ITab>> m_Tabs;
		int m_ActiveIndex;
	};

}